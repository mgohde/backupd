#include "backupconfig.h"

backupconf_t *readBakConfig(char *filename)
{
    FILE *f;
    backupconf_t *cfg;
    char *linebuf;
    char *tokbuf;
    size_t linelen;
    ssize_t checkLen;
    
    if(filename==NULL)
    {
        return NULL;
    }
    
    f=fopen(filename, "r");
    
    if(f==NULL)
    {
        return NULL;
    }
    
    cfg=(backupconf_t*) malloc(sizeof(backupconf_t));
    linebuf=NULL;
    
    do
    {
        linelen=0;
        linebuf=NULL;
        
        checkLen=getline(&linebuf, &linelen, f);
        
        if(checkLen>0 && linebuf!=NULL)
        {
            if(linebuf[0]!='#')
            {
                tokbuf=strtok(linebuf, " \n");
                
                if(tokbuf!=NULL)
                {
                    if(!strcmp(tokbuf, "source:"))
                    {
                        cfg->src=strdup(strtok(NULL, " \n"));
                    }
                    
                    else if(!strcmp(tokbuf, "dest:"))
                    {
                        cfg->dest=strdup(strtok(NULL, " \n"));
                    }
                    
                    else if(!strcmp(tokbuf, "filetype:"))
                    {
                        tokbuf=strtok(NULL, " \n");
                        cfg->extension=getExtPluginCanHandle(tokbuf);
                        
                        if(cfg->extension==-1)
                        {
                            fprintf(stderr, "ERROR: Couldn't find plugin to handle extension %s\n", tokbuf);
                            fprintf(stderr, "File: %s\n", filename);
                            fclose(f);
                            free(linebuf);
                            return NULL;
                        }
                    }
                    
                    else if(!strcmp(tokbuf, "backuptype:"))
                    {
                        tokbuf=strtok(NULL, " \n");
                        cfg->baktype=getBakPluginCanHandle(tokbuf);
                        
                        if(cfg->baktype==-1)
                        {
                            fprintf(stderr, "ERROR: Couldn't find plugin to handle backup type %s\n", tokbuf);
                            fprintf(stderr, "File: %s\n", filename);
                            fclose(f);
                            free(linebuf);
                            return NULL;
                        }
                    }
                }
            }        
        }
        
        if(linebuf!=NULL)
        {
            free(linebuf);
        }
    } while(checkLen>=0);
    
    fclose(f);
    
    return cfg;
}