#ifndef __UCIPC_H__
#define __UCIPC_H__

#include "uci.h"

/**
 * ucipc_get_errorstr: Get an error string for the last uci error
 * @prefix: prefix for the error message
 * @dest: target pointer for the string
 *
 * Note: dest string must be freed by the caller
 */
extern void ucipc_get_errorstr( const char *prefix, char **dest );

/**
 * ucipc_change_callback: to be passed to ucbi_foreach_change()
 * @cmd: the UCI_CMD_xxx indicator for this change
 * @config: name of config being committed
 * @section: section name
 * @option: option name
 * @value: value
 * @userdata: the userdata passed into ucipc_foreach_change()
 */
typedef void (*ucipc_change_callback)(enum uci_command cmd,
				      const char *config,	
				      const char *section,
				      const char *option,
				      const char *value,
				      void       *userdata);
/**
 * ucipc_foreach_change: Execute a callback for each pending uci change
 * @cfg: config to query changes on.  If NULL, then do all configs
 * @cb: callback function
 * @userdata: user defined data that is also passed on to the callback
 */
extern int ucipc_foreach_change( const char *cfg, 
				 ucipc_change_callback cb,
				 void *userdata);

#endif
