#include "plugins.h"

void initPlugins()
{
    //int i;
    aepTabLen=32;
    aepTab=(AEP*) malloc(sizeof(AEP*)*32);
    
    bepTabLen=32;
    bepTab=(BEP*) malloc(sizeof(BEP*)*32);
    
    lastAvailableAEPEntry=0;
    lastAvailableBEPEntry=0;
}

void deInitPlugins()
{
    int i;
    
    for(i=0;i<lastAvailableAEPEntry;i++)
    {
        //TODO: Consider adding de-initialization functions to the plugin ABI.
        dlclose(aepTab[i].rawData);
    }
    
    for(i=0;i<lastAvailableBEPEntry;i++)
    {
        dlclose(bepTab[i].rawData);
    }
    
    free(aepTab);
    free(bepTab);
}

int installPlugin(char *filename)
{
    void *plugin;
    int *pluginType;
    int i;
    
    plugin=dlopen(filename, RTLD_LAZY);
    
    printf("Attempting to load plugin from file: %s\n", filename);
    
    if(plugin==NULL)
    {
        fprintf(stderr, "ERROR: Could not load plugin: %s\n", filename);
        fprintf(stderr, "Dlerror: %s\n", dlerror());
        return 0;
    }
    
    pluginType=(int*)dlsym(plugin, "pluginType");
    printf("Plugin type: %d\n", (*pluginType));
    
    if((*pluginType)==PLUGIN_TYPE_AEP)
    {
        i=lastAvailableAEPEntry;
        
        aepTab[i].rawData=plugin;
        
        //The pointer returned should be a pointer to a string, thus the char** type.
        aepTab[i].name=(*((char**) dlsym(plugin, "name")));
        printf("Plugin name: %s\n", aepTab[i].name);
        
        //Get functions within the plugin:
        aepTab[i].init=(void (*)()) dlsym(plugin, "init");
        aepTab[i].canHandle=(int (*)(char*)) dlsym(plugin, "canHandle");
        aepTab[i].run=(int (*)(char *, char*)) dlsym(plugin, "run");
        aepTab[i].getExtension=(const char* (*)()) dlsym(plugin, "getExtension");
        lastAvailableAEPEntry++;
        
        //Now initialize the plugin:
        aepTab[i].init();
    }
    
    else if((*pluginType)==PLUGIN_TYPE_BEP)
    {
        i=lastAvailableBEPEntry;
        
        aepTab[i].rawData=plugin;
        
        bepTab[i].name=(*((char**) dlsym(plugin, "name")));
        printf("Plugin name: %s\n", bepTab[i].name);
        
        bepTab[i].init=(void (*)()) dlsym(plugin, "init");
        bepTab[i].extInit=(void (*)(char*)) dlsym(plugin, "extInit");
        bepTab[i].needsExtendedInit=(int (*)()) dlsym(plugin, "needsExtendedInit");
        bepTab[i].canHandle=(int (*)(char*)) dlsym(plugin, "canHandle");
        bepTab[i].run=(int (*)(char*, char*, AEP*)) dlsym(plugin, "run");
        lastAvailableBEPEntry++;
        
        //Determine whether this plugin needs extended or normal initialization:
        if(bepTab[i].needsExtendedInit())
        {
            //TODO: Implement a function to search for the BEP's config file.
        }
        
        else
        {
            bepTab[i].init();
        }
    }
    
    else
    {
        fprintf(stderr, "ERROR: plugin %s has invalid plugin type: %d\n", filename, (*pluginType));
        dlclose(plugin);
        return 0;
    }
    
    return 1;
}

plugindesc getBakPluginCanHandle(char *extstr)
{
    plugindesc i;
    
    for(i=0;i<lastAvailableBEPEntry;i++)
    {
        if(bepTab[i].canHandle(extstr))
        {
            return i;
        }
    }
    
    return -1;
}

plugindesc getExtPluginCanHandle(char *extstr)
{
    plugindesc i;
    
    for(i=0;i<lastAvailableAEPEntry;i++)
    {
        if(aepTab[i].canHandle(extstr))
        {
            return i;
        }
    }
    
    return -1;
}

AEP *getExtPlugin(plugindesc desc)
{
    if(desc>-1)
    {
        return aepTab[i];
    }
    
    else
    {
        return NULL;
    }
}

BEP *getBakPlugin(plugindesc desc)
{
    if(desc>-1)
    {
        return bepTab[i];
    }
    
    else
    {
        return NULL;
    }
}

void installAllPlugins(serverconfig_t *cfg)
{
    DIR *dirPtr;
    struct dirent *entry;
    char *buf;
    
    dirPtr=opendir(cfg->pluginDir);
    
    if(dirPtr==NULL)
    {
        fprintf(stderr, "ERROR: Plugin directory %s cannot be opened.", cfg->pluginDir);
        return;
    }
    
    //TODO: Consider checking file extension to distinguish between sofiles and conf files.
    while((entry=readdir(dirPtr)))
    {
        buf=(char*) malloc(sizeof(char)*(strlen(entry->d_name)+strlen(cfg->pluginDir)+100));
        sprintf(buf, "%s/%s", cfg->pluginDir, entry->d_name);
        installPlugin(buf);
        free(buf);
    }
    
    closedir(dirPtr);
}