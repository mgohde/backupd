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
}

void runFixedCfg(char *cfgpath)
{
    
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