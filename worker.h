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

//Encapsulates all data required of the scheduler.
typedef struct
{
    backupconf_t **schedTab;
    int schedTabLen;
    int lastAllocatedSchedTabEntry;
    pthread_t schedulerThread;
} schedtab_t;

int dispatch(char *confPath);
int installTask(char *confPath);
int installRepeatedTasks(char *confDir);
void *backupKernel(void *conf);
void runFixedCfg(char *cfgpath);
void threadTerminateCallback(pthread_t thread);

//Functions for worker storage, etc.
worker_t *createWorkerStruct(worker_t *parent, worker_t *child);
void deleteWorkerStorage(worker_t **root);
void addWorker(worker_t **root, worker_t *w);

//Functions for backup task scheduling functionality:
schedtab_t *initScheduler(int schedTabSize);
int addSchedulerJob(backupconf_t *b, schedtab_t *tab);
void *schedulerKernel(void *arg);
int startScheduler(schedtab_t *tab);
void deleteSchedTab(schedtab_t **tab);

#endif