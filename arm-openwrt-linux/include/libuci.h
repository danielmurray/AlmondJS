/* 
 * File:   main.h
 * Author: shreeman
 *
 * Created on 22 October, 2013, 11:12 AM
 */

#ifndef LIBUCI2_H
#define	LIBUCI2_H
#ifdef __cplusplus
extern "C"
{
#endif 
#include "uci.h"

#define MAX_ARGS	4 /* max command line arguments for batch mode */

void uci_usage(void);
void cli_perror(void);
int package_cmd(int cmd, char *tuple);
int uci_do_package_cmd(int cmd, int argc, char **argv);
void uci_show_value(struct uci_option *o);
int uci_do_section_cmd(int cmd, int argc, char **argv);
int uci_do_add(int argc, char **argv);
int uci_cmd(int argc, char **argv);
int uci_settings(int argc, char **argv);

#ifdef __cplusplus
}
#endif
#endif	/* LIBUCI2_H */

