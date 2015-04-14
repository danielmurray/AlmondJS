#ifndef _CSMI_IM_USER_H_
#define _CSMI_IM_USER_H_
#include <stdint.h>
typedef unsigned char uchar_t;

typedef enum {
  CSMI_IM_BLK_TYPE_OTHER = 0,
  CSMI_IM_BLK_TYPE_DIR,
  CSMI_IM_BLK_TYPE_FS,
  CSMI_IM_BLK_TYPE_DATA,
  CSMI_IM_BLK_TYPE_FILE
} csmi_im_blk_type_e;

typedef enum {
  CSMI_IM_BLK_ZIP_NONE = 0,
  CSMI_IM_BLK_ZIP_GZIP,
  CSMI_IM_BLK_ZIP_BZIP2,
  CSMI_IM_BLK_ZIP_LZMA,
  CSMI_IM_BLK_ZIP_LZO,
  CSMI_IM_BLK_ZIP_ZIP
} csmi_im_zip_type_e;

// Opaque user handles
//
typedef void* csmi_im_sh_t;
typedef void* csmi_im_bh_t;

// enum to string, string to enum
//
extern char *csmi_im_blk_type_to_str( csmi_im_blk_type_e e );
extern csmi_im_blk_type_e csmi_im_blk_type_from_str( char *s );
extern char *csmi_im_zip_type_to_str( csmi_im_zip_type_e e );
extern csmi_im_zip_type_e csmi_im_zip_type_from_str( char *s );

// Return a string rep. of an md5 value
extern char *csmi_im_md5_as_string( unsigned char arr[16] );

// Misc
extern int csmi_im_sh_check_magic( uint32_t m );
extern int csmi_im_bh_check_magic( uint32_t m );
extern int csmi_im_sh_check_md5( csmi_im_sh_t handle, uint32_t blens[] );

// Given an open file, print out information about
// the SH and BHs
//
extern void csmi_im_info( int fd );

// Other print functions
extern void csmi_im_sh_print( csmi_im_sh_t handle, uint32_t lens[] );
extern void csmi_im_bh_print( csmi_im_bh_t handle );

// SH access routines
//
extern uint32_t csmi_im_sh_magic( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_size( csmi_im_sh_t handle );
extern uchar_t *csmi_im_sh_md5( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_im_version( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_sw_version( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_buildid( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_payload_sz( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_chip_bitmap( csmi_im_sh_t handle );
extern uint32_t csmi_im_sh_board_bitmap( csmi_im_sh_t handle );
extern uint8_t  csmi_im_sh_blocks( csmi_im_sh_t handle );

extern void csmi_im_sh_set_magic( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_size( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_md5( csmi_im_sh_t handle, uchar_t val[16] );
extern void csmi_im_sh_set_im_version( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_sw_version( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_buildid( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_payload_sz( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_chip_bitmap( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_board_bitmap( csmi_im_sh_t handle, uint32_t val );
extern void csmi_im_sh_set_blocks( csmi_im_sh_t handle, uint8_t val );

// BH access routines

extern uint32_t csmi_im_bh_magic( csmi_im_bh_t handle );
extern uint32_t csmi_im_bh_size( csmi_im_bh_t handle );
extern uchar_t *csmi_im_bh_md5( csmi_im_bh_t handle );
extern uint32_t csmi_im_bh_sw_version( csmi_im_bh_t handle );
extern char    *csmi_im_bh_name( csmi_im_bh_t handle );
extern uint32_t csmi_im_bh_group( csmi_im_bh_t handle );
extern uint32_t csmi_im_bh_compressed( csmi_im_bh_t handle );
extern uint32_t csmi_im_bh_rsvd( csmi_im_bh_t handle );
extern csmi_im_blk_type_e csmi_im_bh_blk_type( csmi_im_bh_t handle );
extern csmi_im_zip_type_e csmi_im_bh_zip_type( csmi_im_bh_t handle );
extern char    *csmi_im_bh_destination( csmi_im_bh_t handle );

extern void csmi_im_bh_set_magic( csmi_im_bh_t handle, uint32_t val );
extern void csmi_im_bh_set_size( csmi_im_bh_t handle, uint32_t val );
extern void csmi_im_bh_set_md5( csmi_im_bh_t handle, uchar_t val[16] );
extern void csmi_im_bh_set_sw_version( csmi_im_bh_t handle, uint32_t val );
extern void csmi_im_bh_set_name( csmi_im_bh_t handle, char *name );
extern void csmi_im_bh_set_group( csmi_im_bh_t handle, uint32_t val );
extern void csmi_im_bh_set_compressed( csmi_im_bh_t handle, uint32_t val );
extern void csmi_im_bh_set_rsvd( csmi_im_bh_t handle, uint32_t val );
extern void csmi_im_bh_set_blk_type( csmi_im_bh_t handle, csmi_im_blk_type_e e );
extern void csmi_im_bh_set_zip_type( csmi_im_bh_t handle, csmi_im_zip_type_e );
extern void csmi_im_bh_set_destination( csmi_im_bh_t handle, char *dest );

// Take a chunk of memory assumed to be a SH, validate it
// and return a handle to it.
//
extern csmi_im_sh_t csmi_im_sh_validate( void *buffer );

// Create a new sh, return a handle
//
extern csmi_im_sh_t csmi_im_sh_new
( int		tempfd,		// temporary open file no. to hold payload
  uint32_t      im_version,
  uint32_t      sw_version,
  uint32_t      buildid,
  uint32_t      chip_bitmap,
  uint32_t      board_bitmap );

// Create a new bh, return a handle
//
extern csmi_im_bh_t csmi_im_bh_new
( uint32_t      sw_version,
  char         *name,
  uint32_t      group,
  uint32_t      compressed,
  csmi_im_blk_type_e blk_type,
  csmi_im_zip_type_e blk_zip,
  char         *destination );

// Add a block to a sh
//
extern csmi_im_bh_t csmi_im_sh_add_block
( csmi_im_sh_t  sh_handle,
  csmi_im_bh_t	bh_handle,
  void 	       *payload, int payload_sz,
  int fd );  // if payload, else file

// Finialize, after adding all blocks
//
extern int csmi_im_finalize
( csmi_im_sh_t  handle, 
  int finalfd );	// final open file no. for image

#endif
