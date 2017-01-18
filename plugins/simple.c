/* Directly backs up one explicitly named source directory to one
 * explicitly named file. No more, no less.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../plugins.h"


//Plugin header:
int pluginType=2;
char *name="simple";

backupdsupport_t *supportLib;

int canHandle(char *extType)
{
    return !strcmp(extType, name);
}

int needsExtendedInit()
{
    return 0;
}

void init(backupdsupport_t *supportStruct)
{
    supportLib=supportStruct;
}

void extInit(char *confFileName)
{
    //Still don't need init.
}

int run(char *inpath, char *outpath, AEP *requestedArchive)
{
    char *archiveName;
    char *outputPath;
    
    archiveName=supportLib->getLastPathTok(inpath);
    
    if(archiveName!=NULL)
    {
        outputPath=(char*) malloc(sizeof(char)*(strlen(outpath)+strlen(archiveName)+20));
        sprintf(outputPath, "%s/%s", outpath, archiveName);
        requestedArchive->run(inpath, outputPath);
        
        free(archiveName);
        free(outputPath);
    }
    
    else
    {
        fprintf(stderr, "[simple_plugin] ERROR: Could not determine archive name for path %s\n", inpath);
    }
}