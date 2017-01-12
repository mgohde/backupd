#ifndef DAEMON_H
#define DAEMON_H

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

#define LISTEN_QUEUE_LEN 64

//Starts the daemon process.
void daemonize(char *pidfilename, serverconfig_t **scfg);

//Does initialization and command server tasks.
void serverstart(char *pidfilename, serverconfig_t **scfg);
#endif