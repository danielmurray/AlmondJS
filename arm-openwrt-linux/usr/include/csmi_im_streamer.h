#ifndef _CSMI_IM_STREAMER_H_
#define _CSMI_IM_STREAMER_H_

#include "csmi_im_user.h"

// This is the prototype of the send callback that
// the application supplies, and gets called when
// payload data is available.  It gets called with
// a block header handle, the index of the block
// in the image file (starting from 0), and payload
// data.  When size is 0, then there's no more data
// and the payload is complete.  This function should
// return the number of bytes handled.  If it returns
// less than 'size', the streamer will error out.
//
typedef int (*csmi_im_strm_send_cb_t)(csmi_im_bh_t bh, int bidx, 
				      uchar_t *buffer, int size,
				      void *cb_data);

// This callback gets called after the superheader is parsed by
// the streamer and validated against its md5 signature.  It
// is passed the superheader handle, the block length array
// and the application callback data.  This callback may be used
// to check sw_version, and may be used to check the availability
// of resources for storing payload data (calculated from the
// block_lengths array).  It should return 1 if success, 0 if
// fail.  Returning a 0 will halt the streamer.
//
typedef int (*csmi_im_strm_sh_cb_t)(csmi_im_sh_t sh, 
				    int blk_hdr_sz,  // subtracted from each block length, yeilds payload size
				    uint32_t block_lengths[],
				    void *cb_data);

typedef int (*csmi_im_strm_write_cb_t)(csmi_im_bh_t bh, int bidx, 
                    uchar_t *buffer,int offset, int size, void *cb_data );
// Opaque context handle for the streamer
//
// Usage:
//
// csmi_im_strm_context_t c = csmi_im_strm_initialize( send_sb );
// while( <there's data> ) {
//   int status = cmsi_im_strm_update( c, buffer, len );
//   if ( status != len ) {
//     printf( "Error: %s\n", csmi_im_strm_errormsg( c ) );
//   }
// }
//
typedef void* csmi_im_strm_context_t;

// Initialize the streamer context
//
extern csmi_im_strm_context_t csmi_im_strm_initialize
( csmi_im_strm_sh_cb_t sh_cb, csmi_im_strm_send_cb_t cb, 
  void *cb_data, int debug );


extern csmi_im_strm_context_t csmi_im_pri_initialize
( csmi_im_strm_sh_cb_t sh_cb, csmi_im_strm_send_cb_t cb,csmi_im_strm_write_cb_t write_cb, 
  void *cb_data, int debug );

// Clean it up when done
extern void csmi_im_strm_cleanup( csmi_im_strm_context_t handle );

// Is there an error?
//
extern int csmi_im_strm_iserror( csmi_im_strm_context_t handle );

// The error message
extern char *csmi_im_strm_errormsg( csmi_im_strm_context_t handle );

// The streamer.  See usage above.
//
extern int cmsi_im_strm_update( csmi_im_strm_context_t handle, 
				uchar_t *buffer, int size );

extern int cmsi_im_strm_write( csmi_im_strm_context_t handle, 
                int offset ,uchar_t *buffer, int size );

// After everything is done, and if there were no errors,
// the application can retrieve information about the image.
//
extern csmi_im_sh_t  csmi_im_strm_get_sh( csmi_im_strm_context_t handle );
extern uint32_t     *csmi_im_strm_get_block_lengths( csmi_im_strm_context_t handle );
extern csmi_im_bh_t *csmi_im_strm_get_block_headers( csmi_im_strm_context_t handle );
extern void *csmi_im_strm_get_cb_data( csmi_im_strm_context_t handle );

// This function will reset the streamer context to the last
// known "good point" in the streaming process, returning the
// last known good byte index in the stream.  This can be used
// for situations where partial retransmission is possible.
// Good points in the stream are the beginning of the stream,
// and at block header bounderies.
//
// If the streamer update function fails, the calling application
// can call this function.  The return value is the byte offset
// from the beginning of the image to the last known good boundery,
// which the application can send to the image server to start
// retransmission at that point.
//
extern uint32_t csmi_im_strm_reset( csmi_im_strm_context_t handle );

#endif
