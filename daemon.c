#include "daemon.h"

void daemonize(char *pidfilename, serverconfig_t **scfg)
{
    pid_t pid, sid;
    FILE *pidfile;
    FILE *newstdout, *newstderr;
    serverconfig_t *cfg;
    
    cfg=(*scfg);
    
    //Check if the PID file already exists:
    pidfile=fopen(pidfilename, "r");
    
    if(pidfile!=NULL)
    {
        fclose(pidfile);
        printerr("ERROR: PID file exists! Either another instance is running or terminated unexpectedly.\n");
        exit(EXIT_FAILURE);
    }
    
    //Fork to detatch from the calling terminal or process:
    pid=fork();
    
    //This code will be executed as the parent.
    if(pid)
    {
        //Write a new PID to file:
        pidfile=fopen(pidfilename, "w");
        fprintf(pidfile, "%d", pid);
        fclose(pidfile);
        freeConfig(scfg);
        exit(EXIT_SUCCESS);
    }

    //Set file creation mask bits so that created files will have default flags.
    umask(0);
    
    //Now create a process group, of which this daemon is the leader:
    sid=setsid();
    
    if(sid<0)
    {
        exit(EXIT_FAILURE);
    }
    
    //TODO: error checking
    chdir("/");
    
    //Attempt to open logs:
    newstdout=fopen(cfg->msgLogPath, "a");
    newstderr=fopen(cfg->errLogPath, "a");
    
    if(newstdout==NULL || newstderr==NULL)
    {
        printerr("ERROR: Cannot open both error and message log files.\n");
        fprintf(stderr, "Error path given: %s\n", cfg->errLogPath);
        fprintf(stderr, "Message path given: %s\n", cfg->msgLogPath);
        freeConfig(&cfg);
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    stdout=newstdout;
    stderr=newstderr;

    serverstart(pidfilename, scfg);
}

void serverstart(char *pidfilename, serverconfig_t **scfg)
{
    int serversock;
    int clientsock;
    struct sockaddr_un localaddr;
    struct sockaddr clientaddr;
    socklen_t addrlen;
    char runserver;
    serverconfig_t *cfg;
    FILE *clientfile;
    char *cliReq;
    size_t cliReqSize;
    char *cmd, *arg;
    
    
    cfg=(*scfg);
    
    installAllPlugins(cfg);
    
    serversock=socket(AF_UNIX, SOCK_STREAM, 0);
    
    if(serversock==-1)
    {
        printerr("ERROR: could not create UNIX domain socket.\n");
        remove(pidfilename);
        exit(EXIT_FAILURE);
    }
    
    memset(&localaddr, 0, sizeof(struct sockaddr_un));
    
    localaddr.sun_family=AF_UNIX;
    strncpy(localaddr.sun_path, cfg->sockpath, sizeof(localaddr.sun_path)-1);
    
    if(bind(serversock, (struct sockaddr*) &localaddr, sizeof(struct sockaddr_un))==-1)
    {
        printerr("ERROR: could not bind UNIX domain socket to path:\n");
        fprintf(stderr, "%s\n", cfg->sockpath);
        freeConfig(&cfg);
        exit(EXIT_FAILURE);
    }
    
    if(listen(serversock, LISTEN_QUEUE_LEN)==-1)
    {
        printerr("ERROR: cannot listen to server socket.\n");
        freeConfig(&cfg);
        exit(EXIT_FAILURE);
    }
    
    runserver=1;
    
    while(runserver)
    {
        cliReq=NULL;
        cliReqSize=0;
        
        addrlen=sizeof(struct sockaddr);
        clientsock=accept(serversock, &clientaddr, &addrlen);
        
        clientfile=fdopen(clientsock, "w+");
        
        //Wait for a command:
        getline(&cliReq, &cliReqSize, clientfile);
        cmd=strtok(cliReq, " \t\n");
        
        //Write the command back:
        if(!strcmp(cmd, "EXIT"))
        {
            free(cliReq);
            fclose(clientfile);
            break;
        }
        
        else if(!strcmp(cmd, "BACKUP"))
        {
            
        }
        
        else if(!strcmp(cmd, "RELOADCFG"))
        {
            
        }
        
        else if(!strcmp(cmd, ""))
        {
            
        }
        
        else
        {
            fprintf(clientfile, "ERROR\n");
        }
        
        fprintf(clientfile, "%s", cliReq);
        free(cliReq);
        
        fclose(clientfile);
    }
    
    //Close and delete the server socket:
    close(serversock);
    remove(cfg->sockpath);
    
    //Now remove our pid file:
    remove(pidfilename);
}