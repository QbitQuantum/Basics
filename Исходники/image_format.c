size_t format_image(uint8_t **out, int render_fmt, int misc_int, VInfo *ji, uint8_t *buf) {
#ifdef HAVE_WINDOWS
  char tfn[64] = "";
#endif
#ifdef __USE_XOPEN2K8
  size_t rs = 0;
  FILE *x = open_memstream((char**) out, &rs);
#else
  FILE *x = tmpfile();
#endif
#ifdef HAVE_WINDOWS
  if (!x) {
    // wine and ancient version of windows don't support tmpfile()
    // srand is per thread :(
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec * tv.tv_usec * 100000);
    snprintf(tfn, sizeof(tfn), "harvid.tmp.%d", rand());
    x = fopen(tfn, "w+b"); // we should really use open(tfn, O_RDWR | O_CREAT | O_EXCL, 0600); and fdopen
  }
#endif
  if (!x) {
    dlog(LOG_ERR, "IMF: tmpfile() creation failed.\n");
    return(0);
  }

  switch (render_fmt) {
    case 1:
      {
        if (misc_int < 5 || misc_int > 100)
          misc_int = JPEG_QUALITY;
      if (write_jpeg(ji, buf, misc_int, x))
        dlog(LOG_ERR, "IMF: Could not write jpeg\n");
      break;
      }
    case 2:
      if (write_png(ji, buf, x))
        dlog(LOG_ERR, "IMF: Could not write png\n");
      break;
    case 3:
      if (write_ppm(ji, buf, x))
        dlog(LOG_ERR, "IMF: Could not write ppm\n");
      break;
    default:
        dlog(LOG_ERR, "IMF: Unknown outformat %d\n", render_fmt);
        fclose(x);
        return 0;
      break;
  }
#ifdef __USE_XOPEN2K8
  fclose(x);
  return rs;
#elif defined HAVE_WINDOWS
  if (strlen(tfn) > 0) {
    fclose(x);
    x = fopen(tfn, "rb");
  } else {
    fflush(x);
  }
#else
  fflush(x);
#endif
  /* re-read image from tmp-file */
  fseek (x , 0 , SEEK_END);
  long int rsize = ftell (x);
  rewind(x);
  if (fseek(x, 0L, SEEK_SET) < 0) {
    dlog(LOG_WARNING, "IMF: fseek failed\n");
  }
  fflush(x);
  *out = (uint8_t*) malloc(rsize*sizeof(uint8_t));
  if (fread(*out, sizeof(char), rsize, x) != rsize) {
    dlog(LOG_WARNING, "IMF: short read. - possibly incomplete image\n");
  }
  fclose(x);
#ifdef HAVE_WINDOWS
  if (strlen(tfn) > 0) {
    unlink(tfn);
  }
#endif
  return (rsize);
}