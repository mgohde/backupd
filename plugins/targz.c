/* targz.c -- AEP representing a gzipped tarball.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Define some constant plugin identification data:
char *name="targz";
int pluginType=1;

void init()
{
    
}

//canHandle should be usable both in reading backup configuration files
//(ie. the strcmp for targz) and actual paths on disk (.tar.gz).
int canHandle(char *extType)
{
    return !strcmp(extType, "targz") || !strcmp(extType, ".tar.gz");
}

//This makes it easier to implement rolling backups, etc. where information
//may be encoded in the filename.
const char *getExtension()
{
    return ".tar.gz";
}

//Ultimately, it's up to the BEP to decide on file naming
//conventions and such. All the AEP is expected to do is provide
//an appropriate file extension.
int run(char *srcDir, char *destDir)
{
    char *runStr;
    int retV;
    
    runStr=(char*) malloc(sizeof(char)*(strlen(destDir)+strlen(srcDir)+100));
    
    sprintf(runStr, "tar -czf %s.tar.gz %s", destDir, srcDir);
    retV=system((const char*) runStr);
    
    free(runStr);
    return retV==0;
}