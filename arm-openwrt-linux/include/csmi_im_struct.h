#ifndef _CSMI_IM_STRUCT_H_
#define _CSMI_IM_STRUCT_H_
/*
 * Structures defining software image download
 */
#include <stdint.h>

#define CSMI_SH_MAGIC 0xa4411376
#define CSMI_BH_MAGIC 0xb4411376

#define SHORT_STRING_SZ 32
#define LONG_STRING_SZ  64
typedef char short_string_t[SHORT_STRING_SZ];
typedef char long_string_t[LONG_STRING_SZ];

typedef struct {
  uint32_t	magic;		// magic number for super header
  uint32_t	size;		// total size of sh, including magic and size
  uchar_t	md5[16];	// MD5, covers everything after md5
  uint32_t	im_version;	// image tool version
  uint32_t	sw_version;	// sw version
  uint32_t	buildid;	// build id
  uint32_t	payload_sz;	// total size of payload, minus sh
  uint32_t	chip_bitmap;	// supported chips
  uint32_t	board_bitmap;	// supported boards
  uint8_t	blocks;		// number of blocks in payload
  // This struct will be followed by an array of block lengths
} __attribute__((packed)) csmi_im_sh_s;

typedef struct {
  uint32_t	magic;		// magic number for block header
  uint32_t	size;		// size of bh, including magic and size
  uchar_t	md5[16];	// MD5, covers everything after md5
  uint32_t	sw_version;	// sw version
  short_string_t name;		// to identify the block by name
  union {
    struct {
      uint32_t	group       :1;	// This block is part of a group
      uint32_t	compressed  :1;	// This block is compressed
      uint32_t	rsvd       :29; // reserved
    } bit;
    uint32_t bits;
  } flags;
  csmi_im_blk_type_e blk_type;	// What type of block is this?
  csmi_im_zip_type_e blk_zip;	// if compressed, how?
  long_string_t	destination;	// where this block goes
} __attribute__((packed)) csmi_im_bh_s;

#endif
