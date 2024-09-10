int mg_get_raw_doc(void *qd, u_long docnum, unsigned char **p_ucbuf, 
		    int *p_ucbuf_len, int *p_retlen)
{
  query_data *real_qd ;
  static last_pos = 0 ;
  static u_char *c_buffer = NULL ;
  u_long pos, len ;
  int newucbuf_len ;
  int temp_retlen, temp_ucbuf_len ;

  if (p_retlen == NULL) p_retlen = &temp_retlen ;
  if (p_ucbuf_len == NULL) {
    p_ucbuf_len = &temp_ucbuf_len ;
    *p_ucbuf_len = 0 ;
  }

  real_qd = (query_data *)qd ;
  FetchDocStart(real_qd, docnum, &pos, &len) ;
  newucbuf_len = (int)(real_qd->td->cth.ratio * 1.01 * len)+101 ;

  if (c_buffer != NULL)
    Xfree(c_buffer) ;
  if (!(c_buffer = Xmalloc(len)))
    return -1 ;

  if (newucbuf_len > *p_ucbuf_len) {
    if (*p_ucbuf != NULL) 
      Xfree(*p_ucbuf) ;
    if (!(*p_ucbuf = Xmalloc(newucbuf_len))) 
      return -1 ;
    *p_ucbuf_len = newucbuf_len ;
  }
  if (last_pos != pos)
    Fseek(real_qd->td->TextFile, pos, 0) ;
  Fread(c_buffer, 1, len, real_qd->td->TextFile) ;
  last_pos = pos+len ;
  DecodeText(real_qd->cd, c_buffer, len, *p_ucbuf, p_retlen) ;
  (*p_ucbuf)[*p_retlen]='\0' ;
  return 0 ;
}