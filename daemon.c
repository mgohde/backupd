#include "daemon.h"

void daemonize(char *pidfilename, serverconfig_t *cfg)
{
    pid_t pid, sid;
    FILE *pidfile;
    FILE *newstdout, *newstderr;
    
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
        freeConfig(&cfg);
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

    serverstart(pidfilename, cfg);
}

void serverstart(char *pidfilename, serverconfig_t *cfg)
{
    int serversock;
    int sockdesc;
    struct sockaddr_un localaddr;
    
    serversock=socket(AF_UNIX, SOCK_STREAM, 0);
    
    if(serversock==-1)
    {
        printerr("ERROR: could not create UNIX domain socket.\n");
        remove(pidfilename);
        exit(EXIT_FAILURE);
    }
    
    memset(&localaddr, 0, sizeof(struct sockaddr_un));
    
    localaddr.sun_family=AF_UNIX;
    strncopy(localaddr.sun_path, cfg->sockpath, sizeof(localaddr.sun_path)-1);
    
    if(bind(serversock, (struct sockaddr*) &localaddr, sizeof(struct sockaddr_un))==-1)
    {
        printerr("ERROR: could not bind UNIX domain socket to path:\n");
        fprintf(stderr, "%s\n", cfg->sockpath);
        freeConfig(&cfg);
        exit(EXIT_FAILURE);
    }
    
    if(listn(serversock, LISTEN_QUEUE_LEN)==-1)
    {
        printerr("ERROR: cannot listen to server socket.\n");
        freeConfig(&cfg);
        exit(EXIT_FAILURE);
    }
}