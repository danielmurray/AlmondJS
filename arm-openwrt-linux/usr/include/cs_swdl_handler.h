#ifndef _CS_SWDL_HANDLER_H_
#define _CS_SWDL_HANDLER_H_

#include "csmi_im_streamer.h"

/*
 * Application interface to swdl handlers.
 */

// This callback is used when the image download is finished
// and no errors were detected by the image stream processor.
// This callback is responsible for committing the payload 
// data.
//
typedef int (*cs_swdl_process_t)(csmi_im_strm_context_t im_context,
				 void *cb_data );

// This callback is called when there is payload data available
// to the application.  This callback should store this payload
// in some temporary way, to be finally handled during the
// cs_swdl_process() callback.
//
typedef int (*cs_swdl_payload_t)(csmi_im_bh_t bh, int bidx, 
                         uchar_t *buffer, int size, void *cb_data );

// This callback gets called after the superheader is parsed by
// the streamer and validated against its md5 signature.  It
// is passed the superheader handle, the block length array
// and the application callback data.  This callback may be used
// to check sw_version, and may be used to check the availability
// of resources for storing payload data (calculated from the
// block_lengths array).  It should return 1 if success, 0 if
// fail.  Returning a 0 will halt the streamer.
//
typedef int (*cs_swdl_sheader_t)(csmi_im_sh_t sh,
				 int blk_hdr_sz,
				 uint32_t block_lengths[],
				 void *cb_data);

// Called when everything is over, whether it passed or failed.
// This callback is used to cleanup any resources (alloc'd memory,
// temporary files, etc) that might have been allocated during the
// sw download.
//
typedef int (*cs_swdl_cleanup_t)( void *cb_data );

/*Write the image by block*/
typedef int (*cs_swdl_write_t)(csmi_im_bh_t bh, int bidx, 
                         uchar_t *buffer,int offset, int size, void *cb_data );
// Passed into the registeration function (see below) and
// filled out by the handler.
//
typedef struct {
  char 			*name;		 // command line arg that triggers this
  char			*help;		 // help string
  cs_swdl_sheader_t	sheader_handler; // superheader handling function
  cs_swdl_payload_t	payload_handler; // payload handling function
  cs_swdl_process_t	process_handler; // image processing function
  cs_swdl_write_t	write_handler; // image write function
  cs_swdl_cleanup_t	cleanup_handler; // image cleanup function
  void			*callback_data;  // handler callback data
} cs_swdl_handler_t;

// Called by the main program.  Must parse my own command line
// options, and install my callbacks and callback data into
// the context.  Called exactly once during the lifetime of
// a swdl manager.
//
extern int registration( int argc, char *argv[],
			 int verbose, int validate, int commit,
			 cs_swdl_handler_t *context );

// Called by the main program before processing a new
// image file.  Could be called multiple times during
// the lifetime of a swdl manager.
//
extern int initialize( cs_swdl_handler_t *context, void *cb_data );

// Handle superheader validation
//
extern int sheader_handler(csmi_im_sh_t sh,
				 int blk_hdr_sz,
				 uint32_t block_lengths[],
				 void *cb_data);

// Handle payload streaming.
//
extern int payload_handler(csmi_im_bh_t bh, int bidx,
			   unsigned char *buffer, int size, void *cb_data);

// The image has been downloaded and the payloads extracted.
// This function now processes those payloads, performing
// the nessesary actions to install the payloads into
// permenent storage.
//
extern int process_handler(csmi_im_strm_context_t im_context, void *cb_data);

extern int write_handler(csmi_im_bh_t bh, int bidx, uchar_t *buffer,int offset, int size, void *cb_data ); 

// An image processing has finished, either for good or bad.  This
// function can perform any cleanup of resources used during the
// download process.
//
extern int cleanup_handler( void *cb_data);

#endif
