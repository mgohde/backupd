/* bakrotate.c -- Implementation of a rotating backup job as a 
 * backupd plugin.
 */

#include "../plugins.h"
 
//Header to satisfy the ABI and plugin loader:
int pluginType=2;
char *name="bakrotate";

int canHandle(char *extType)
{
    
}

int needsExtendedInit()
{
    
}

void init()
{
    
}

void extInit(char *confFileName)
{
    //Unimplemented, because we need no init.
}

int run(char *inpath, char *outpath, AEP *requestedArchive)
{
    
}