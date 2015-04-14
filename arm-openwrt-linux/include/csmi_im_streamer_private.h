#ifndef _CSMI_IM_STREAMER_PRIVATE_H_
#define _CSMI_IM_STREAMER_PRIVATE_H_

typedef enum {
  CSMI_IM_STATE_SH_INCOMPLETE = 0,
  CSMI_IM_STATE_BL_INCOMPLETE,
  CSMI_IM_STATE_BH_INCOMPLETE,
  CSMI_IM_STATE_WORKING_ON_FILE,
  CSMI_IM_STATE_INERROR
} csmi_im_state_e;

typedef struct {
  csmi_im_state_e	state;
  char			errormsg[128];
  csmi_im_strm_send_cb_t  send_cb;
  csmi_im_strm_write_cb_t write_cb;
  csmi_im_strm_sh_cb_t    sh_cb;
  void			*cb_data;
  uchar_t		debug;

  uint32_t		total_bytes;

  csmi_im_sh_s 		*sh;
  uint32_t		sh_ptr;
  struct MD5Context	sh_md5_context;
  uchar_t		sh_skipped;

  csmi_im_bh_s 		*bh;
  uint32_t		bh_ptr;
  struct MD5Context	bh_md5_context;
  uchar_t		bh_skipped;

  uint32_t		pld_len;
  uint32_t		pld_ptr;

  csmi_im_bh_s 		**bhdrs;
  int 			num_blocks;

  uint32_t 		block_lengths[ 256 ];
  uint32_t		bl_ptr;

  uint32_t		last_good_boundery;
} csmi_im_strm_context_s;

#endif
