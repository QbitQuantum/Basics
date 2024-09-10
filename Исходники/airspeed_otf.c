/* airspeed_otf_parse */
void airspeed_otf_parse(char c)
{
  static unsigned char otf_status = OTF_UNINIT, otf_idx = 0, otf_crs_idx;
  static char otf_inp[64];
  static unsigned int counter;
  static short course[3];
  static unsigned int altitude;
  static unsigned char checksum;

  switch (otf_status) {

  case OTF_WAIT_START:
    if (c == OTF_START) {
      otf_status++;
      otf_idx = 0;
    } else {
      otf_status = OTF_UNINIT;
    }
    break;

  case OTF_WAIT_COUNTER:
    if (isdigit((int)c)) {
      if (otf_idx == 0) {
//FIXME        otf_timestamp = getclock();
      }
      otf_inp[otf_idx++] = c;
    } else {
      if ((otf_idx == 5) && (c == OTF_LIMITER)) {
        otf_inp[otf_idx] = 0;
        counter = atoi(otf_inp);
        otf_idx = 0;
        otf_crs_idx = 0;
        otf_status++;
      } else {
        otf_status = OTF_UNINIT;
      }
    }
    break;

  case OTF_WAIT_ANGLES:
    if (isdigit((int)c) || (c == '-') || (c == '.')) {
      otf_inp[otf_idx++] = c;
    } else {
      if ((otf_idx > 1) && (otf_idx < 9) && (c == OTF_LIMITER)) {
        otf_inp[otf_idx] = 0;
        course[otf_crs_idx] = (int16_t) (100. * atof(otf_inp));
        otf_idx = 0;
        if (otf_crs_idx++ == 2) {
          otf_status++;
        }
      } else {
        otf_status = OTF_UNINIT;
      }
    }
    break;

  case OTF_WAIT_ALTITUDE:
    if (isdigit((int)c) || (c == '-') || (c == '.')) {
      otf_inp[otf_idx++] = c;
    } else {
      if ((otf_idx > 1) && (otf_idx < 9) && (c == OTF_LIMITER)) {
        otf_inp[otf_idx] = 0;
        altitude = (int32_t) (100. * atof(otf_inp));
        otf_idx = 0;
        otf_status++;
      } else {
        otf_status = OTF_UNINIT;
      }
    }
    break;

  case OTF_WAIT_CHECKSUM:
    if (isxdigit((int)c)) {
      otf_inp[otf_idx++] = c;
    } else {
      if ((otf_idx == 2) && (c == OTF_END)) {
        otf_inp[otf_idx] = 0;
        checksum = strtol(otf_inp, NULL, 16);
        otf_idx = 0;
        DOWNLINK_SEND_FLOW_AP_OTF(DefaultChannel, DefaultDevice, &counter, &course[0], &course[1], &course[2], &altitude, &checksum);
      }
      otf_status = OTF_UNINIT;
    }
    break;

  default:
    otf_status = OTF_UNINIT;
    break;
  }
}