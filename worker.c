#include "worker.h"

void *backupKernel(backupconf_t *conf)
{
    
}

void runFixedCfg(char *cfgpath)
{
    
}

int dispatch(char *confPath)
{
    backupconf_t *cfg;
    
    cfg=readBakConfig(confPath);
    
    if(cfg==NULL)
    {
        return 0;
    }
    
    else
    {
        //TODO: Implement an actual thread pool so that threads can be explicitly terminated when the daemon is told to exit.
    }
}