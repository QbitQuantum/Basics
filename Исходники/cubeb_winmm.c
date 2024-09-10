static cubeb_device_pref
winmm_query_preferred_in_device(UINT devid)
{
  DWORD mmpref = WAVE_MAPPER, compref = WAVE_MAPPER, status;
  cubeb_device_pref ret = CUBEB_DEVICE_PREF_NONE;

  if (waveInMessage((HWAVEIN)(size_t)WAVE_MAPPER, DRVM_MAPPER_PREFERRED_GET,
        (DWORD_PTR)&mmpref, (DWORD_PTR)&status) == MMSYSERR_NOERROR &&
      devid == mmpref)
    ret |= CUBEB_DEVICE_PREF_MULTIMEDIA | CUBEB_DEVICE_PREF_NOTIFICATION;

  if (waveInMessage((HWAVEIN)(size_t)WAVE_MAPPER, DRVM_MAPPER_CONSOLEVOICECOM_GET,
        (DWORD_PTR)&compref, (DWORD_PTR)&status) == MMSYSERR_NOERROR &&
      devid == compref)
    ret |= CUBEB_DEVICE_PREF_VOICE;

  return ret;
}