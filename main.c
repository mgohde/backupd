/*
 * backupd - a daemon to continuously manage backup tasks on a system.
 * 
 * Current assumptions:
 *  * That a program-wide configuration file is stored in /etc/backupd.conf
 *  * That individual system-wide backup jobs are stored in 
 */
 
#include <stdio.h>

#include "daemon.h"
#include "serverconfig.h"
#include "utils.h"
#include "plugins.h"

void printHelp(char *exename)
{
	fprintf(stderr, "Usage: %s [option] [file]\n", exename);
	printerr("Where [option] is one of the following:\n");
	printerr("\t-d  Forks into a daemon process. [file] should be a PID file.\n");
	printerr("\t-r  Attempts to run a backup job or update an existing config\n");
	printerr("\t\tfile. [file] should be a configuration filename.\n");
	printerr("\t-sj Prints the status of all backup jobs.\n");
	printerr("\t-sp Prints the status of all loaded plugins.\n");
	printerr("\t-c  Reloads all configuration files.\n");
    printerr("\t-x  Requests that backupd terminate.\n");
}

void runDaemon(char *pidfilename, char *configfilename)
{
    serverconfig_t *cfg;
    
    if(configfilename==NULL)
    {
        cfg=genDefaultConfig();
    }
    
    else
    {
        cfg=loadConfig(configfilename);
        
        if(cfg==NULL)
        {
            cfg=genDefaultConfig();
        }
    }
    
    daemonize(pidfilename, &cfg);
}

void runBackupJob(char *backupConfig)
{
    makeConnection(DEFAULT_SOCK_PATH, "BACKUP", backupConfig);
}

void printJobStatus()
{
    
}

void printPluginStatus()
{
}

void reloadConfig()
{
    
}

void exitBackupd()
{
    makeConnection(DEFAULT_SOCK_PATH, "EXIT", "dummytext");
}

void handleArgs(int argc, char **argv)
{
    int i;
    
    char *filename1, *filename2;
    char d, r, sj, sp, c, x;
    
    filename1=NULL;
    filename2=NULL;
    d=0;
    r=0;
    sj=0;
    sp=0;
    c=0;
    x=0;
    
	if(argc==1)
	{
		printHelp(argv[0]);
	}
	
	else
	{
        //TODO: consider not manually handling args.
		for(i=1;i<argc;i++)
        {
            if(!strcmp(argv[i], "-d"))
            {
                d=1;
            }
            
            else if(!strcmp(argv[i], "-r"))
            {
                r=1;
            }
            
            else if(!strcmp(argv[i], "-sj"))
            {
                sj=1;
            }
            
            else if(!strcmp(argv[i], "-sp"))
            {
                sp=1;
            }
            
            else if(!strcmp(argv[i], "-c"))
            {
                c=1;
            }
            
            else if(!strcmp(argv[i], "-x"))
            {
                x=1;
            }
            
            else
            {
                if(filename1!=NULL)
                {
                    filename2=argv[i];
                }
                
                else
                {
                    filename1=argv[i];
                }
            }
        }
        
        //Now dispatch based on the parameters given:
        
        if(d)
        {
            runDaemon(filename1, filename2);
        }
        
        else if(r)
        {
            runBackupJob(filename1);
        }
        
        else if(sp)
        {
            
        }
        
        else if(sj)
        {
            
        }
        
        else if(c)
        {
            
        }
        
        else if(x)
        {
            exitBackupd();
        }
        
        else
        {
            printHelp(argv[0]);
        }
	}
}

int main(int argc, char **argv)
{
    //int retV;
    handleArgs(argc, argv);
    
    //Attempt to load a plugin:
    /*
    initPlugins();
    retV=installPlugin("/home/mgohde/codeliteworkspace/backupd/Release/targz.so");
    if(retV)
    {
        printf("Plugin install success!\n");
    }
    
    else
    {
        printf("Failure!\n");
    }
    
    printf("Can plugin handle targz? %d\n", aepTab[0].canHandle("targz"));
    deInitPlugins();
    */
    return 0;
}
