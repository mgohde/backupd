#include "daemon.h"

void daemonize(char *pidfilename)
{
	pid_t pid, sid;
	FILE *pidfile;
	
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
		fwrite(pidfile, "%d", pid);
		fclose(pidfile);
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
	
	chdir("/");
	//TODO: Implement log writing
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	serverstart(pidfilename);
}

void serverstart(char *pidfilename)
{
	
}