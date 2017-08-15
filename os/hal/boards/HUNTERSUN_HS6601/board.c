/*
    ChibiOS - Copyright (C) 2006-2014 Giovanni Di Sirio
              Copyright (C) 2014-2016 HunterSun Technologies
                 pingping.wu@huntersun.com.cn

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "lib.h"

#if HAL_USE_CODEC || defined(__DOXYGEN__)

static const hs_codec_eqpara_t g_stDefaultEq =
{
  {80, 320, 640, 1280, 2560, 5120, 10240},
  {0,  3,   3,   0,    -3,   -3,    1},
};

static const hs_codec_boardinfo_t g_stCodecInfo = 
{
  HS_PIN_AUDIO_PA, 
  1,                    /* PA on level */
  
  0,                    /* drv gain, 0: -6db, 1: 0db */
  1,                    /* drv output, 0: differential output,  1: single-end output */

  #if __CHIP_PACKAGE_48PIN_
  TRACK_RR,             /* mic select, 28pin-package: TRACK_LL, 48pin-package: TRACK_RR */
  #else
  TRACK_LL,
  #endif

  1,                    /* pga gain for linein */
  5,                    /* pga gain for mic */

  1,                    /* package select, Current packets of HS6601A2 all select '1' */

  0,                    /* mixed left and right of dac enable */
  0,                    /* mixed left and right of adc enable */

  0,                   	/* dac <=  26db */ 
  -42,                  /* dac >= -47db */

  24,                   /* adc <=  24db */
  -20,                  /* adc >= -47db */

  -9,                   /* hfp max gain of playing */
  24,                   /* adc default gain, just for hfp */

  &g_stDefaultEq  ,
};
#endif


static const SFConfig g_stSfCfg = 
{
    NULL,
    WIDTH_8BIT,
    SELECT_CS0,
    CLKMODE_0,
    LOW_ACTIVE,
    96000000,
};

#if HAL_USE_SDC || defined(__DOXYGEN__)
static const SDCConfig g_stSdCfg = 
{
  24000000
};
#endif


void _board_pinmuxInit(void) 
{
}

/* analog circuit calibration routines will take effect XTAL, audio CODEC, BT, FM etc */
void _board_anaCalibration(void)
{
  pmu_cali_rc();
  pmu_cali_ldo();
}

void hs_boardInit(void)
{
  _board_anaCalibration();
  _board_pinmuxInit();
  
  sfStart(&SFD, &g_stSfCfg);
  sfProbe(&SFD, TIME_INFINITE);
  
  #if HAL_USE_SERIAL && HS_SERIAL_USE_UART1
  sdStart(&SD1, NULL);
  #endif

  #if HAL_USE_SDC
  sdcStart(&SDCD0, &g_stSdCfg);
  #endif

  #if HAL_USE_AUDIO
  audioStart();
  #endif
  
}

void hs_boardUninit(void)
{
  sfStop(&SFD);

  #if HAL_USE_SDC
  sdcStop(&SDCD0);
  #endif  
}

NOINLINE float hs_boardGetKeyVolt(uint8_t u8Idx)
{
  if(u8Idx >= HS_ADCKEY_MAXNUM)
    return 1000.0;

  return 0;
}

NOINLINE void boardKickWatchDog(void)
{
  #if HAL_USE_WDT || defined(__DOXYGEN__)
  wdtKickdog();
  #else
  __NOP();
  #endif
}

#if HAL_USE_CODEC || defined(__DOXYGEN__)
NOINLINE const hs_codec_boardinfo_t *hs_boardGetCodecInfo(void)
{
  return &g_stCodecInfo;
}
#endif


/*
 * }
 */

