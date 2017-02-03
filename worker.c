#include "worker.h"

void *backupKernel(void *conf)
{
    backupconf_t *cfg;
    AEP *aep;
    BEP *bep;
    
    cfg=(backupconf_t*) conf;
    
    //Use the plugin given to execute the backup job:
    aep=getExtPlugin(cfg->extension);
    bep=getBakPlugin(cfg->baktype);
    
    bep->run(cfg->src, cfg->dest, aep);
    
    freeBakConfig(&cfg);
    
    return NULL;
}

//Note: This kernel function should eventually be capable of recieving pthread_cancel requests.
//Second note: this function should also scan for plugin reloads, etc.
void *repeatedBackupKernel(void *conf)
{
    backupconf_t *cfg;
    AEP *aep;
    BEP *bep;
    time_t curTime;
    struct tm *usableTime;
    
    cfg=(backupconf_t*) conf;
    
    aep=getExtPlugin(cfg->extension);
    bep=getBakPlugin(cfg->baktype);
    
    //Should be changed to respond to requests.
    while(1)
    {
        curTime=time(NULL);
        usableTime=localtime(&curTime);
        
        //Check the time thingy
        if(1)
        {
            bep->run(cfg->src, cfg->dest, aep);
        }
        
        free(usableTime);
    }
}

void runFixedCfg(char *cfgpath)
{
    
}

//Should be automatically called by dispatch() as necessary.
int installTask(char *confPath)
{
    return 0;
}

//Reads through the repeated task directory, then
//attempts to install all configuration files present.
int installRepeatedTasks(char *confDir)
{
    DIR *d;
    struct dirent *e;
    char *tmp;
    char *tok1, *tok2;
    char *confPath;
    
    d=opendir(confDir);
    
    while((e=readdir(d)))
    {
        tmp=strdup(e->d_name);
        
        tok1=strtok(tmp, ".");
        tok2=strtok(NULL, ".");
        
        if(tok2!=NULL)
        {
            if(!strcmp(tok2, "conf"))
            {
                confPath=(char*) malloc(sizeof(char) * (strlen(tok2)+strlen(confDir)+10));
                
                if(confDir[strlen(confDir)-1]=='/')
                {
                    sprintf(confPath, "%s%s", confDir, e->d_name);
                }
                
                else
                {
                    sprintf(confPath, "%s/%s", confDir, e->d_name);
                }
                
                installTask(confPath);
                
                free(confPath);
            }
        }
        
        free(tmp);
    }
    
    return 1;
}

int dispatch(char *confPath)
{
    backupconf_t *cfg;
    pthread_t childthread;
    worker_t *workerDescrip;
    int retV;
    
    cfg=readBakConfig(confPath);
    
    if(cfg==NULL)
    {
        fprintf(stderr, "ERROR: could not read given configuration file: %s\n", confPath);
        fprintf(stderr, "       Was it passed with an absolute path?\n");
        return 0;
    }
    
    else
    {
        //Spawn the thread without actually adding it to a thread pool (yet).
        retV=pthread_create(&childthread, NULL, backupKernel, (void*) cfg);
        
        if(retV)
        {
            fprintf(stderr, "ERROR: could not spawn worker thread!\n");
            return 0;
        }
        
        //TODO: Implement an actual thread pool so that threads can be explicitly terminated when the daemon is told to exit.
    }
    
    return 1;
}

/* The following functions implement a worker management data structure: */

worker_t *createWorkerStruct(worker_t *parent, worker_t *child)
{
    worker_t *w;
    
    w=(worker_t *) malloc(sizeof(worker_t));
    w->parent=parent;
    w->child=child;
    
    return w;
}

void deleteWorkerStorage(worker_t **root)
{
    worker_t *w, *tmp;
    
    w=(*root);
    
    while(w!=NULL)
    {
        tmp=w->child;
        free(w);
        w=tmp;
    }
    
    (*root)=NULL;
}

void addWorker(worker_t **root, worker_t *w)
{
    if(!(*root))
    {
        (*root)=w;
    }
    
    else
    {
        (*root)->parent=w;
        w->child=(*root);
        (*root)=w;
    }
}

schedtab_t *initScheduler(int schedTabSize)
{
    schedtab_t *retTab;
    
    retTab=(schedtab_t*) malloc(sizeof(schedtab_t));
    retTab->schedTabLen=schedTabSize;
    retTab->schedTab=(backupconf_t **) malloc(sizeof(backupconf_t*)*schedTabSize);
    retTab->lastAllocatedSchedTabEntry=0;
    
    return retTab;
}

int startScheduler(schedtab_t *tab)
{
    return pthread_create(&(tab->schedulerThread), NULL, schedulerKernel, tab);
}

int addSchedulerJob(backupconf_t *b, schedtab_t *tab)
{
    int retV;
    
    retV=0;
    
    if(tab->lastAllocatedSchedTabEntry>=tab->schedTabLen)
    {
        return 0;
    }
    
    else
    {
        tab->schedTab[tab->lastAllocatedSchedTabEntry]=b;
        tab->lastAllocatedSchedTabEntry++;
        
        return 1;
    }
}

void *schedulerKernel(void *arg)
{
    //TODO: implement scheduler kernel logic and such.
    return NULL;
}

void deleteSchedTab(schedtab_t **tab)
{
    int i;
    schedtab_t *localT;
    
    localT=(*tab);
    
    for(i=0;i<localT->lastAllocatedSchedTabEntry;i++)
    {
        freeBakConfig(&(localT->schedTab[i]));
    }
    
    free(localT->schedTab);
    free((*tab));
    (*tab)=NULL;
}