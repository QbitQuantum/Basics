/* params : desc : the document descriptor
 *          buf  : destination buffer for UTF-16 data
 * return : the length of the paragraph
 *          NO_MORE_DATA if there is no more paragraph
 *          ERR_STREAMFILE if an error occured
 *
 * reads the next paragraph and converts to UTF-16
 */
int p_read_content(struct doc_descriptor *desc, UChar *buf) {
  char *outputbuf, *src;
  UChar *dest;
  int len;
  UErrorCode err;

  len = 0;

  outputbuf = (char *) malloc(INTERNAL_BUFSIZE);

  /* reading the next paragraph */
  memset(outputbuf, '\x00', INTERNAL_BUFSIZE);
  len = parse(desc, outputbuf);
  
  if (len > 0) {
    (desc->nb_par_read) += 1;

    /* converting to UTF-16 */
    err = U_ZERO_ERROR;
    dest = buf;
    src = outputbuf;
    ucnv_toUnicode(desc->conv, &dest, dest + 2*INTERNAL_BUFSIZE,
		   &src, outputbuf + strlen(outputbuf), NULL, FALSE, &err);
    len = 2*(dest - buf);
    if (U_FAILURE(err)) {
      free(outputbuf);
      outputbuf = NULL;
      fprintf(stderr, "Unable to convert buffer\n");
      return ERR_ICU;
    }

  }

  if(outputbuf != NULL) {
    free(outputbuf);
  }

  return len;
}