#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SYS_CONF_DIR "/etc/backup.d"
#define DEFAULT_PLUGIN_DIR "/usr/local/backupd/plugins"
#define DEFAULT_ERR_LOG "/usr/local/backupd/error.log"
#define DEFAULT_MSG_LOG "/usr/local/backupd/message.log"
#define DEFAULT_SOCK_PATH "/usr/local/backupd/backupd.sock"

//This structure contains all server configuration stuff.
typedef struct
{
    char *systemConfFileDir;
    char *pluginDir;
    char *errLogPath;
    char *msgLogPath;
    char *sockpath;
} serverconfig_t;

serverconfig_t *loadConfig(char *filename);
serverconfig_t *genDefaultConfig();
void storeConfig(char *filename, serverconfig_t *cfg);
void freeConfig(serverconfig_t **cfg);

#endif