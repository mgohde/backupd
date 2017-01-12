/*
 * plugins.h -- Definitions for plugin support.
 * 
 * backupd is designed to be able to handle a wide array of
 * different backup schemes and filetypes. As such, it makes use of
 * plugins to add functionality 
 * 
 * There are two types of plugins:
 *  1. Archive extension plugins
 *     - Implement specific compression schemes, such as gzipped tarballs.
 *  2. Backup extension plugins
 *     - Implement specific backup types, such as rolling backups.
 * 
 * All plugins must be implemented in a thread-safe way outside of their init() functions.
 * 
 * Archive extension plugins should be more or less stateless. Ideally, they should just
 * wrap an existing external executable, like tar.
 * 
 * Backup extension plugins implement specific backup routines or procedures. When initialized,
 * they are provided with a table of functions in backupd as well as an optional configuration file
 * path if passed by the user. If the user does not pass a configuration, then the backup extension
 * plugin should resort to sane defaults.
 */
 
#ifndef PLUGINS_H
#define PLUGINS_H

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#include "serverconfig.h"

typedef int plugindesc;

#define PLUGIN_TYPE_AEP 1
#define PLUGIN_TYPE_BEP 2

//Define an Archive Extension Plugin
typedef struct
{
    void *rawData;
    char *name;
    int (*canHandle)(char *extType);
    void (*init)();
    int (*run)(char *inpath, char *outfile);
    const char *(*getExtension)();
} AEP;

//Define a Backup Extension Plugin
typedef struct
{
    void *rawData;
    char *name;
    int (*canHandle)(char *extType);
    int (*needsExtendedInit)();
    void (*init)();
    void (*extInit)(char *confFileName);
    int (*run)(char *inpath, char *outpath, AEP *requestedArchive);
} BEP;

//(for now) Define plugin arrays for ease of implementation.
//Later on, plugins descriptions should be stored in a linked list or equivalent.
AEP *aepTab;
size_t aepTabLen;
size_t lastAvailableAEPEntry;

BEP *bepTab;
size_t bepTabLen;
size_t lastAvailableBEPEntry;

void initPlugins();
void deInitPlugins();
void installAllPlugins(serverconfig_t *cfg);
int installPlugin(char *filename);

AEP *getExtPlugin(plugindesc desc);
plugindesc getExtPluginCanHandle(char *extstr);

BEP *getBakPlugin(plugindesc desc);
plugindesc getBakPluginCanHandle(char *extstr);
#endif