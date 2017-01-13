/* bakrotate.c -- Implementation of a rotating backup job as a 
 * backupd plugin.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../plugins.h"
 
//Header to satisfy the ABI and plugin loader:
int pluginType=2;
char *name="bakrotate";

#define LASTUSEDFILENAME "count.dat"

int canHandle(char *extType)
{
    return !strcmp("bakrotate", extType);
}

int needsExtendedInit()
{
    return 0;
}

void init()
{
    //Do nothing
}

void extInit(char *confFileName)
{
    //Unimplemented, because we need no initialization.
}

int run(char *inpath, char *outpath, AEP *requestedArchive)
{
    DIR *d;
    FILE *f;
    struct dirent *entry;
    char *countFilename;
    char *outputFilename;
    char *inPathDup;
    char *pathFilename;
    char *tmp;
    int curNum;
    FILE *otherf;
    
    otherf=fopen("/usr/local/backupd/bakrotate.log", "w");
    fprintf(otherf, "[bakrotate]\tExecuting job with type %s for %s -> %s\n", " ", inpath, outpath);//, requestedArchive->getExtension());
    fclose(otherf);
    
    //First, scan the output directory for the last file number used:
    d=opendir(outpath);
    
    if(d==NULL)
    {
        return 0;
    }
    
    countFilename=(char*) malloc((strlen(LASTUSEDFILENAME)+strlen(outpath)+20)*sizeof(char));
    sprintf(countFilename, "%s/%s", outpath, LASTUSEDFILENAME);
    
    while((entry=readdir(d)))
    {
        if(!strcmp(entry->d_name, "count.dat"))
        {
            f=fopen(countFilename, "r");
            fscanf(f, "%d", &curNum);
            fclose(f);
        }
    }
    
    closedir(d);
    
    inPathDup=strdup(inpath);
    pathFilename=strtok(inPathDup, "/"); //Split the path
    
    //Get the last element of the path:
    //(Note: It would be nice if backupd or the user did this for the plugin)
    while((tmp=strtok(NULL, "/")))
    {
        pathFilename=tmp;
    }
    
    outputFilename=(char*) malloc(sizeof(char)*(strlen(pathFilename)+strlen(outpath)+20));
    sprintf(outputFilename, "%s/%s", outpath, pathFilename);
    
    //TODO: Size estimation and rotation.
    
    requestedArchive->run(inpath, outputFilename);
    
    curNum++;
    f=fopen(countFilename, "w");
    fprintf(f, "%d", curNum);
    
    free(inPathDup);
    free(countFilename);
    free(outputFilename);
}