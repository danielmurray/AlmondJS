#include "configargs.h"

static char basever[] = "4.5.2";
static char datestamp[] = "20101126";
static char devphase[] = "Linaro";
static char revision[] = "[release 4.5-2010.12-0]";

/* FIXME plugins: We should make the version information more precise.
   One way to do is to add a checksum. */

static struct plugin_gcc_version gcc_version = {basever, datestamp,
						devphase, revision,
						configuration_arguments};
