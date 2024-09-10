/* num should be greater than or equal to 1 */
int 
RawDocOutput (query_data * qd, u_long num, FILE * Output)
{
  static last_pos = 0;
  static u_char *c_buffer = 0;
  static int buf_len = -1;
  static u_char *uc_buffer = 0;
  u_long pos, len;
  int ULen;

  FetchDocStart (qd, num, &pos, &len);

  if ((int) len > buf_len)
    {
      if (c_buffer)
	{
	  Xfree (c_buffer);
	  Xfree (uc_buffer);
	}
      if (!(c_buffer = Xmalloc (len)))
	return -1;
      if (!(uc_buffer = Xmalloc ((int) (qd->td->cth.ratio * 1.01 *
					len) + 100)))
	return -1;
      buf_len = len;
    }
  if (last_pos != pos)
    Fseek (qd->td->TextFile, pos, 0);
  Fread (c_buffer, 1, len, qd->td->TextFile);
  last_pos = pos + len;
  DecodeText (qd->cd, c_buffer, len, uc_buffer, &ULen);
  fwrite (uc_buffer, ULen, sizeof (u_char), Output);
  return 0;
}