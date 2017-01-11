/*
 * plugins.h -- Definitions for plugin support.
 * 
 * backupd is designed to be able to handle a wide array of
 * different backup schemes and filetypes. As such, it makes use of
 * plugins to add functionality 
 * 
 * There are two types of plugins:
 *  1. Archive extension plugins
 *     - Implement specific compression schemes, such as gzipped tarballs.
 *  2. Backup extension plugins
 *     - Implement specific backup types, such as rolling backups.
 * 
 * All plugins must be implemented in a thread-safe way outside of their init() functions.
 * 
 * Archive extension plugins should be more or less stateless. Ideally, they should just
 * wrap an existing external executable, like tar.
 * 
 * Backup extension plugins implement specific backup routines or procedures. When initialized,
 * they are provided with a table of functions in backupd as well as an optional configuration file
 * path if passed by the user. If the user does not pass a configuration, then the backup extension
 * plugin should resort to sane defaults.
 */
 
#ifndef PLUGINS_H
#define PLUGINS_H

#endif