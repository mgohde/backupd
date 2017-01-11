/*
 * backupd - a daemon to continuously manage backup tasks on a system.
 * 
 * Current assumptions:
 *  * That a program-wide configuration file is stored in /etc/backupd.conf
 *  * That individual system-wide backup jobs are stored in 
 */
 
#include <stdio.h>
#include "utils.h"

void printHelp(char *exename)
{
	fprintf(stderr, "Usage: %s [option] [file]\n");
	printerr("Where [option] is one of the following:\n");
	printerr("\t-d  Forks into a daemon process. [file] should be a PID file.\n");
	printerr("\t-r  Attempts to run a backup job or update an existing config\n");
	printerr("\t\tfile. [file] should be a configuration filename.\n");
	printerr("\t-sj Prints the status of all backup jobs.\n");
	printerr("\t-sp Prints the status of all loaded plugins.\n");
	printerr("\t-c  Reloads all configuration files.\n");
}

void handleArgs(int argc, char **argv)
{
	if(argc==1)
	{
		printHelp(argv[0]);
	}
	
	else
	{
		
	}
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}
