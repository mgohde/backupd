/* worker.h -- Definitions for backupd's threaded worker pool. 
 */

#ifndef WORKER_H
#define WORKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "plugins.h"
#include "backupconfig.h"

typedef struct wrkr
{
    char *src;
    char *dest;
    plugindesc archivePlugin;
    plugindesc backupPlugin;
    pthread_t thread;
    
    struct wrkr *child, *parent;
} worker_t;

//worker_t *root=NULL;

int dispatch(char *confPath);
void *backupKernel(void *conf);
void runFixedCfg(char *cfgpath);

worker_t *createWorkerStruct(worker_t *parent, worker_t *child);

#endif