/* This plugin is an "AEP" that enables 
 * BEPs to determine how much space is available
 * on a given volume.
 * 
 * This is its own plugin to show additional
 * uses of the AEP execution model.
 */

#include <string.h>

/* Header: */
char *name="getfreespace";
int pluginType=1;

void init()
{
    /* Do nothing. */
}

int canHandle(char *extType)
{
    return !strcmp(extType, "freespace");
}

const char *getExtension()
{
    return "freespace";
}

int run(char *srcDir, char *destDir)
{
    //TODO: figure this out.
    return 0;
}