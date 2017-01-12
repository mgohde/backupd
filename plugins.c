#include "plugins.h"

void initPlugins()
{
    int i;
    aepTabLen=32;
    aepTab=(AEP*) malloc(sizeof(AEP*)*32);
    
    bepTabLen=32;
    bepTab=(BEP*) malloc(sizeof(BEP*)*32);
    
    lastAvailableAEPEntry=0;
    lastAvailableBEPEntry=0;
}

int installPlugin(char *filename)
{
    void *plugin;
    int *pluginType;
    int i;
    
    plugin=dlopen(filename, RTLD_LAZY);
    
    if(plugin==NULL)
    {
        fprintf(stderr, "ERROR: Could not load plugin: %s\n", filename);
        return 0;
    }
    
    pluginType=(int*)dlsym(plugin, "pluginType");
    
    if((*pluginType)==PLUGIN_TYPE_AEP)
    {
        i=lastAvailableAEPEntry;
        
        aepTab[i].rawData=plugin;
        
        //The pointer returned should be a pointer to a string, thus the char** type.
        aepTab[i].name=(*((char**) dlsym(plugin, "name")));
        
        //Get functions within the plugin:
        aepTab[i].init=(void (*)()) dlsym(plugin, "init");
        aepTab[i].canHandle=(int (*)()) dlsym(plugin, "canHandle");
        aepTab[i].run=(int (*)(char *, char*)) dlsym(plugin, "run");
        lastAvailableAEPEntry++;
    }
    
    else if((*pluginType)==PLUGIN_TYPE_BEP)
    {
        i=lastAvailableBEPEntry;
        
        aepTab[i].rawData=plugin;
        
        bepTab[i].name=(*((char**) dlsym(plugin, "name")));
        
        bepTab[i].init=(void (*)()) dlsym(plugin, "init");
        bepTab[i].extInit=(void (*)(char*)) dlsym(plugin, "extInit");
        bepTab[i].needsExtendedInit=(int (*)()) dlsym(plugin, "needsExtendedInit");
        bepTab[i].canHandle=(int (*)(char*)) dlsym(plugin, "canHandle");
        bepTab[i].run=(int (*)(char*, char*, AEP*)) dlsym(plugin, "run");
    }
    
    else
    {
        fprintf(stderr, "ERROR: plugin %s has invalid plugin type: %d\n", filename, (*pluginType));
        dlclose(plugin);
        return 0;
    }
    
    return 1;
}