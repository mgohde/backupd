/* worker.h -- Definitions for backupd's threaded worker pool. 
 */

#ifndef WORKER_H
#define WORKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <time.h>
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

typedef struct task
{
    //TODO: Implement proper task scheduling and such.
} task_t;

//worker_t *root=NULL;

int dispatch(char *confPath);
int installTask(char *confPath);
int installRepeatedTasks(char *confDir);
void *backupKernel(void *conf);
void runFixedCfg(char *cfgpath);
void threadTerminateCallback(pthread_t thread);

worker_t *createWorkerStruct(worker_t *parent, worker_t *child);

#endif