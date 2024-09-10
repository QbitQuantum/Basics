/* minimal header reading.  modify if you want to parse more information */
int RGBE_ReadHeader(FILE *fp, int *width, int *height, rgbe_header_info *info)
{
  char buf[128];
  int found_format;
  float tempf;
  int i;

  found_format = 0;
  if (info) {
    info->valid = 0;
    info->programtype[0] = 0;
    info->gamma = info->exposure = 1.0;
  }
  if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == NULL)
    return rgbe_error(rgbe_read_error,NULL);
  if ((buf[0] != '#')||(buf[1] != '?')) {
    /* if you want to require the magic token then uncomment the next line */
    /*return rgbe_error(rgbe_format_error,"bad initial token"); */
  }
  else if (info) {
    info->valid |= RGBE_VALID_PROGRAMTYPE;
    for(i=0;i<sizeof(info->programtype)-1;i++) {
      if ((buf[i+2] == 0) || isspace(buf[i+2]))
  break;
      info->programtype[i] = buf[i+2];
    }
    info->programtype[i] = 0;
    if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
      return rgbe_error(rgbe_read_error,NULL);
  }
  for(;;) {
#if 0
    if ((buf[0] == 0)||(buf[0] == '\n'))
      return rgbe_error(rgbe_format_error,"no FORMAT specifier found");
#endif
    if (((buf[0] == 0)||(buf[0] == '\n'))&&(found_format == 0))
      return rgbe_error(rgbe_format_error,"no FORMAT specifier found");
    else if (strcmp(buf,"FORMAT=32-bit_rle_rgbe\n") == 0) {
      found_format = 1;
#if 0
      break;       /* format found so break out of loop */
#endif
  }
    else if (info && (sscanf(buf,"GAMMA=%g",&tempf) == 1)) {
      info->gamma = tempf;
      info->valid |= RGBE_VALID_GAMMA;
    }
    else if (info && (sscanf(buf,"EXPOSURE=%g",&tempf) == 1)) {
      info->exposure = tempf;
      info->valid |= RGBE_VALID_EXPOSURE;
    }
    else if (strcmp(buf,"\n") == 0) {
    /* blank line found so break out of loop */
      break;
    }
    if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
      return rgbe_error(rgbe_read_error,NULL);
  }
  if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
    return rgbe_error(rgbe_read_error,NULL);
#if 0
  if (strcmp(buf,"\n") != 0)
    return rgbe_error(rgbe_format_error,
          "missing blank line after FORMAT specifier");
  if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
    return rgbe_error(rgbe_read_error,NULL);
#endif
  if (sscanf(buf,"-Y %d +X %d",height,width) < 2)
    return rgbe_error(rgbe_format_error,"missing image size specifier");
  return RGBE_RETURN_SUCCESS;
}