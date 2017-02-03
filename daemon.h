#ifndef DAEMON_H
#define DAEMON_H

/* daemon.h -- Definitions for the backupd daemon and server core.
 * 
 * The functions here:
 *  1. Daemonize the process
 *  2. Handle incoming connections on the server's communication socket.
 *  3. Manage and act on all regularly scheduled tasks.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

#include "utils.h"
#include "plugins.h"
#include "serverconfig.h"
#include "worker.h"

#define LISTEN_QUEUE_LEN 64

//Starts the daemon process.
void daemonize(char *pidfilename, serverconfig_t **scfg);

//Does initialization and command server tasks.
void serverstart(char *pidfilename, serverconfig_t **scfg);

//Processes each accepted connection.
//Returns 1 if the server should continue running, or 0 if it should terminate.
int handleConnection();

void *schedulerKernel(void *arg);
#endif