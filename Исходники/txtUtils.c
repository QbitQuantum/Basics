int initTxt(struct doc_descriptor *desc) {
  UErrorCode err;
  char *encoding = NULL;
  int len, BOMlength = 0;
  char buf[BUFSIZE];
  UChar outbuf[4*BUFSIZE];


  lseek(desc->fd, 0, SEEK_SET);
  len = read(desc->fd, buf, BUFSIZE);

  /* detect BOM */
  err = U_ZERO_ERROR;
  encoding = ucnv_detectUnicodeSignature(buf, BUFSIZE, &BOMlength, &err);
  if(encoding != NULL) {
    lseek(desc->fd, BOMlength, SEEK_SET);

    /* initialize converter to encoding */
    err = U_ZERO_ERROR;
    desc->conv = ucnv_open(encoding, &err);
    if (U_FAILURE(err)) {
      fprintf(stderr, "unable to open ICU converter\n");
      return ERR_ICU;
    }
    
  } else {
    /* initialize converter to UTF-8 */
    err = U_ZERO_ERROR;
    desc->conv = ucnv_open("utf8", &err);
    if (U_FAILURE(err)) {
      fprintf(stderr, "unable to open ICU converter\n");
      return ERR_ICU;
    }

    /* check the first 2048 bytes */
    err = U_ZERO_ERROR;
    ucnv_setToUCallBack(desc->conv, UCNV_TO_U_CALLBACK_STOP, NULL, NULL, NULL, &err);
    if (U_FAILURE(err)) {
      fprintf(stderr, "error setToUCallback\n");
      return ERR_ICU;
    }
    err = U_ZERO_ERROR;
    ucnv_toUChars(desc->conv, outbuf, 4 * BUFSIZE, buf, len, &err);
    if (U_FAILURE(err)) {
      fprintf(stderr, "Unknown encoding\n");
      return ERR_ICU;
    }
    lseek(desc->fd, 0, SEEK_SET);
  }

  return OK;
}