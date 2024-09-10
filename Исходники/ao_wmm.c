int ao_wmm_set_option(ao_device *device,
                      const char *key, const char *value)
{
  ao_wmm_internal *internal = (ao_wmm_internal *) device->internal;
  int res = 0;

  if (!strcmp(key, "dev")) {
    if (!strcmp(value,"default")) {
      key = "id";
      value = "0";
    } else {
      WAVEOUTCAPS caps;
      int i, max = waveOutGetNumDevs();

      adebug("searching for device %s among %d\n", value, max);
      for (i=0; i<max; ++i) {
        MMRESULT mmres = waveOutGetDevCaps(i, &caps, sizeof(caps));
        if (mmres == MMSYSERR_NOERROR) {
          res = !strcmp(value, caps.szPname);
          adebug("checking id=%d, name='%s', ver=%d.%d  => [%s]\n",
                i,caps.szPname,caps.vDriverVersion>>8,caps.vDriverVersion&255,res?"YES":"no");
          if (res) {
            internal->id   = i;
            internal->caps = caps;
            break;
          }
        } else {
          aerror("waveOutGetDevCaps(%d) => %s",i,mmerror(mmres));
        }
      }
      goto finish;
    }