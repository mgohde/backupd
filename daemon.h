#ifndef DAEMON_H
#define DAEMON_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.h"

//Starts the daemon process.
void daemonize(char *pidfilename);

//Does initialization and command server tasks.
void serverstart(char *pidfilename);
#endif