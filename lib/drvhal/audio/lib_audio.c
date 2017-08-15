/*
    drvhal - Copyright (C) 2012~2016 HunterSun Technologies
                 pingping.wu@huntersun.com.cn
 */

/**
 * @file    lib/drvhal/audio/lib_audio.c
 * @brief   lib_audio file.
 * @details 
 *
 * @addtogroup  lib drvhal
 * @details 
 * @{
 */

#include "lib.h"
#include "math.h"


#if HAL_USE_AUDIO

typedef struct
{
  int16_t  s16Dev[AVOL_DEV_NUM];
}hs_audio_var_t;

static hs_audio_var_t g_stAudioVar;

const hs_codec_boardinfo_t *hs_boardGetCodecInfo(void);


void hs_audio_volSet(hs_avol_dev_t eDev, int16_t s16Vol)
{
  hs_audio_ply_src_t src = eDev == AVOL_DEV_HFP ? AUDIO_PLY_SRC_HFP : 0; 
  int tmpVol;
  
  if(eDev >= AVOL_DEV_NUM)
    return ;  

  tmpVol = audioPlayGetVolumeMax(src);
  if(s16Vol >= tmpVol)
  {
    s16Vol = tmpVol;
    g_stAudioVar.s16Dev[eDev] = s16Vol;

  }

  tmpVol = audioPlayGetVolumeMin(src);
  if(s16Vol <= tmpVol)
  {
    s16Vol = tmpVol;
    g_stAudioVar.s16Dev[eDev] = s16Vol;

    audioPlaySetVolume(s16Vol);
    
    audioPlayMute();
    return ;
  }
  else
  {
    audioPlayUnmute();
  }  

  g_stAudioVar.s16Dev[eDev] = s16Vol;
  //hs_led_disp((eDev << 12) | LED_DISP_VOLUME);
  audioPlaySetVolume(s16Vol);
}

int16_t hs_audio_volGet(hs_avol_dev_t eDev)
{
  if(eDev >= AVOL_DEV_NUM)
    return 0;

  return g_stAudioVar.s16Dev[eDev];
}

uint16_t hs_audio_volGetLvl(hs_avol_dev_t eDev)
{
  hs_audio_ply_src_t src = eDev == AVOL_DEV_HFP ? AUDIO_PLY_SRC_HFP : 0; 
  int16_t s16Max, s16Min;
  uint16_t u16Vol;
  
  if(eDev >= AVOL_DEV_NUM)
    return 0;

  s16Max = audioPlayGetVolumeMax(src);
  s16Min = audioPlayGetVolumeMin(src);

  u16Vol = s16Max - s16Min;
  u16Vol = (g_stAudioVar.s16Dev[eDev] - s16Min) * 32 / u16Vol;

  return u16Vol;  
}

void hs_audio_volRestore(hs_avol_dev_t eDev)
{
  const hs_codec_boardinfo_t *pstInfo;
  
  if(eDev >= AVOL_DEV_NUM)
    return ;

  if(eDev != AVOL_DEV_HFP)
  {
    pstInfo = hs_boardGetCodecInfo();
    hs_codec_setEq(pstInfo->pstDefaultEq);
  }
  
  audioPlaySetVolume(g_stAudioVar.s16Dev[eDev]);
  if(g_stAudioVar.s16Dev[eDev] <= audioPlayGetVolumeMin(0))
    audioPlayMute();
  else
    audioPlayUnmute();
}

#endif

/** @} */
