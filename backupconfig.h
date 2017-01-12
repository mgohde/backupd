#ifndef BACKUPCONFIG_H
#define BACKUPCONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "plugins.h"

typedef struct
{
    char *src, *dest;
    plugindesc extension, baktype;
    //TODO: add fields for task scheduling and such.
} backupconf_t;

backupconf_t *readBakConfig(char *filename);

#endif