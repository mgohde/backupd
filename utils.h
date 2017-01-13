#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include "serverconfig.h"

#define printerr(a) fprintf(stderr, a)

//Sends a command to a running backup process.
int makeConnection(char *sockPath, char *command, char *arg);

#endif