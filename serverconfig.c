#include "serverconfig.h"

serverconfig_t *genDefaultConfig()
{
	serverconfig_t *cfg;
	
	cfg=(serverconfig_t*) malloc(sizeof(serverconfig_t));
	cfg->systemConfFileDir=strdup(DEFAULT_SYS_CONF_DIR);
	cfg->pluginDir=strdup(DEFAULT_PLUGIN_DIR);
	cfg->port=9001;
	return cfg;
}

void storeConfig(char *filename, serverconfig_t *cfg)
{
	FILE *out;
	
	out=fopen(filename, "w");
	
	fprintf(out, "# Generated backupd configuration file.\n\n");
	fprintf(out, "# Directory containing all system-wide backup scripts:");
	fprintf(out, "systemconfdir: %s\n\n", cfg->systemConfFileDir);
	fprintf(out, "# Plugin storage path:");
	fprintf(out, "plugindir: %s\n\n", cfg->pluginDir);
	fprintf(out, "# Port for the daemon to listen to for commands:");
	fprintf(out, "port: %d\n", cfg->port);
	
	fclose(out);
}

void freeConfig(serverconfig_t **cfg)
{
	serverconfig_t *lcfg;
	
	free(lcfg->systemConfFileDir);
	free(lcfg->pluginDir);
	free(lcfg);
	(*cfg)=NULL;
}