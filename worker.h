/* worker.h -- Definitions for backupd's threaded worker pool. 
 */

#ifndef WORKER_H
#define WORKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "plugins.h"

typedef struct
{
    char *src;
    char *dest;
    plugindesc archivePlugin;
    plugindesc backupPlugin;
    pthread_t thread;
} worker_t;

void dispatch(FILE *client, int clientfd);
void *backupKernel();

#endif