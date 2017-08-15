/*
    demo - Copyright (C) 2012~2016 HunterSun Technologies
                 pingping.wu@huntersun.com.cn
 */

/**
 * @file    main.c
 * @brief   a demo process.
 * @details 
 *
 * @addtogroup  demo
 * @details 
 * @{
 */

#include "lib.h"
#ifdef TEST_ENABLE
#include "test.h"
#endif

#include "codec2.h"
#include "sine.h"
#include "dump.h"

int main(void) 
{
  struct CODEC2 *codec2;
  FIL          *fin = (FIL *)hs_malloc(sizeof(FIL), __MT_DMA);
  FIL          *fout = (FIL *)hs_malloc(sizeof(FIL), __MT_DMA);
  short         *buf;
  unsigned char *bits;
  int            nsam, nbit;
  UINT len;

  hs_boardInit(); 

  #ifdef TEST_ENABLE
  hs_test_init();  
  #endif  

  f_open(fin, "0:/in.wav", FA_READ);
  f_open(fout, "0:/out.wav", FA_CREATE_ALWAYS | FA_WRITE);

  if(fin && fout)
  {
    codec2 = codec2_create(CODEC2_MODE_1200);
    nsam = codec2_samples_per_frame(codec2);
    buf = (short*)hs_malloc(nsam*sizeof(short), __MT_GENERAL);
    nbit = codec2_bits_per_frame(codec2);
    bits = (unsigned char*)hs_malloc(nbit*sizeof(char), __MT_GENERAL);

    while(f_read(fin, buf, sizeof(short) * nsam, &len) == FR_OK) 
    {
    	codec2_encode(codec2, bits, buf);
    	codec2_decode(codec2, buf, bits);
    	f_write(fout, buf, sizeof(short) * nsam, &len);
    }

    hs_free(buf);
    hs_free(bits);
    codec2_destroy(codec2);

    f_close(fin);
    f_close(fout);
  }

  while(true) 
  {
    #ifdef TEST_ENABLE
    hs_test_chkExit();
    #endif
    
    msleep(1000);
  }
}
