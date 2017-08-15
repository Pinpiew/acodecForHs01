/*
    drv-hal - Copyright (C) 2012~2016 HunterSun Technologies
                 pingping.wu@huntersun.com.cn
 */

/**
 * @file    drv/drvhal.c
 * @brief   drvhal file.
 * @details 
 *
 * @addtogroup  drvhal
 * @details 
 * @{
 */
#include "lib.h"


int hs_drvhal_init(void)
{
	return 0;
}

void hs_drvhal_uninit(void)
{

}

void boardInit(void) 
{
  cpm_reset_system();
  cpm_init_clock();
  
  halInit();
  oshalKernelInitialize();  

  hs_fatfs_init();
}

