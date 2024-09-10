static int ajoy_sample(FAR const struct ajoy_lowerhalf_s *lower,
                       FAR struct ajoy_sample_s *sample)
{
  struct adc_msg_s adcmsg[SAM_ADC_NCHANNELS];
  FAR struct adc_msg_s *ptr;
  ssize_t nread;
  ssize_t offset;
  int have;
  int i;

  /* Read all of the available samples (handling the case where additional
   * channels are enabled).
   */

  nread = file_read(&g_adcfile, adcmsg,
                    MAX_ADC_CHANNELS * sizeof(struct adc_msg_s));
  if (nread < 0)
    {
      int errcode = get_errno();
      if (errcode != EINTR)
        {
          ierr("ERROR: read failed: %d\n", errcode);
        }

      return -errcode;
    }
  else if (nread < 2 * sizeof(struct adc_msg_s))
    {
      ierr("ERROR: read too small: %ld\n", (long)nread);
      return -EIO;
    }

  /* Sample and the raw analog inputs */

  for (i = 0, offset = 0, have = 0;
       i < SAM_ADC_NCHANNELS && offset < nread && have != 3;
       i++, offset += sizeof(struct adc_msg_s))
    {
      ptr = &adcmsg[i];

      /* Is this one of the channels that we need? */

      if ((have & 1) == 0 && ptr->am_channel == 0)
        {
          int32_t tmp = ptr->am_data;
          sample->as_x = (int16_t)tmp;
          have |= 1;

          iinfo("X sample: %ld -> %d\n", (long)tmp, (int)sample->as_x);
        }

      if ((have & 2) == 0 && ptr->am_channel == 1)
        {
          int32_t tmp = ptr->am_data;
          sample->as_y = (int16_t)tmp;
          have |= 2;

          iinfo("Y sample: %ld -> %d\n", (long)tmp, (int)sample->as_y);
        }
    }

  if (have != 3)
    {
      ierr("ERROR: Could not find joystack channels\n");
      return -EIO;
    }


  /* Sample the discrete button inputs */

  sample->as_buttons = ajoy_buttons(lower);
  iinfo("Returning: %02x\n", AJOY_SUPPORTED);
  return OK;
}