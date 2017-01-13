#include "serverconfig.h"

serverconfig_t *genDefaultConfig()
{
	serverconfig_t *cfg;
	
	cfg=(serverconfig_t*) malloc(sizeof(serverconfig_t));
	cfg->systemConfFileDir=strdup(DEFAULT_SYS_CONF_DIR);
	cfg->pluginDir=strdup(DEFAULT_PLUGIN_DIR);
    cfg->errLogPath=strdup(DEFAULT_ERR_LOG);
    cfg->msgLogPath=strdup(DEFAULT_MSG_LOG);
	cfg->sockpath=strdup(DEFAULT_SOCK_PATH);
	return cfg;
}

serverconfig_t *loadConfig(char *filename)
{
    FILE *in;
    serverconfig_t *config;
    char *linebuf;
    char *tokbuf;
    size_t linesize;
    
    in=fopen(filename, "r");

    if(in==NULL)
    {
        return NULL;
    }
    
    config=genDefaultConfig();
    
    do
    {
        linebuf=NULL;
        linesize=0;
        linesize=getline(&linebuf, &linesize, in);
        
        if(linesize>0)
        {
            //Do work only if the line doesn't contain a comment:
            if(linebuf[0]!='#')
            {
                tokbuf=strtok(linebuf, " ");
                
                if(!strcmp(tokbuf, "systemconfdir:"))
                {
                    config->systemConfFileDir=strdup(strtok(NULL, " "));
                }
                
                else if(!strcmp(tokbuf, "plugindir:"))
                {
                    config->pluginDir=strdup(strtok(NULL, " "));
                }
                
                else if(!strcmp(tokbuf, "socket:"))
                {
                    config->sockpath=strdup(strtok(NULL, " "));
                }
                
                else if(!strcmp(tokbuf, "msglogfile"))
                {
                    config->msgLogPath=strdup(strtok(NULL, " "));
                }
                
                else if(!strcmp(tokbuf, "errlogfile"))
                {
                    config->errLogPath=strdup(strtok(NULL, " "));
                }
            }
        }
        
        if(linesize!=-1)
        {
            free(linebuf);
        }
    } while(linesize!=-1);
    
    fclose(in);
    return config;
}

void storeConfig(char *filename, serverconfig_t *cfg)
{
    FILE *out;
    
    out=fopen(filename, "w");
    
    fprintf(out, "# Generated backupd configuration file.\n\n");
    fprintf(out, "# Directory containing all system-wide backup scripts:\n");
    fprintf(out, "systemconfdir: %s\n\n", cfg->systemConfFileDir);
    fprintf(out, "# Plugin storage path:");
    fprintf(out, "plugindir: %s\n\n", cfg->pluginDir);
    fprintf(out, "# Socket for the daemon to listen to for commands:\n");
    fprintf(out, "socket: %s\n\n", cfg->sockpath);
    fprintf(out, "# Message and error log paths:\n");
    fprintf(out, "msglogfile: %s\n", cfg->msgLogPath);
    fprintf(out, "errlogfile: %s\n", cfg->errLogPath);
    
    fclose(out);
}

void freeConfig(serverconfig_t **cfg)
{
	serverconfig_t *lcfg;
    
    lcfg=(*cfg);
	
	free(lcfg->systemConfFileDir);
	free(lcfg->pluginDir);
    free(lcfg->errLogPath);
    free(lcfg->msgLogPath);
    free(lcfg->sockpath);
	free(lcfg);
    
	(*cfg)=NULL;
}