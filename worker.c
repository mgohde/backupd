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
    
    freeConfig(&cfg);
    
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
    
}

int installRepeatedTasks(char *confDir)
{
    DIR *d;
    struct dirent *e;
    
    d=opendir(confDir);
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