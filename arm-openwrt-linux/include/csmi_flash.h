#ifndef _CSMI_FLASH_H_
#define _CSMI_FLASH_H_

#include "csmi_user.h"

typedef struct {
  char		*device;	// /dev/mtdX
  int		erase_blksz;	// the erase block size for this device
  int		offset;		// of start of sb in device
  csmi_sb_handle_t handle;	// superblock handle
  int		dirty;		// app has modified sb
} csmi_flash_dev_t;

// Read a specified number of superblocks from flash.
// App must supply device, erase_blksz, offset and
// numsecs for each sb.  The function will supply the rest.
// Returns the number of superblocks successfully read.
//
extern int csmi_flash_get_sbs( csmi_flash_dev_t sb[], int num );

// Commit the specified number of superblocks.  Only superblocks
// with 'dirty' set will be written back into flash memory.
// returns 1 on success, 0 on trouble.
//
extern int csmi_flash_commit( csmi_flash_dev_t sb[], int num );

// Commit the specified number of superblocks.  Only superblocks
// with 'dirty' set will be written back into flash memory.
// returns 1 on success, 0 on trouble.  Also frees up allocated
// memory.
//
extern int csmi_flash_commit_and_free( csmi_flash_dev_t sb[], int num );

#endif
