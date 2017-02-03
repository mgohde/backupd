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
    
    //TODO: consider whether fields for backup configuration are good enough.
    int hour;
    int minute;
    unsigned int dayOfMonth;
} backupconf_t;

backupconf_t *genBakConfigStruct();
backupconf_t *readBakConfig(char *filename);

void freeBakConfig(backupconf_t **cfg);

#endif