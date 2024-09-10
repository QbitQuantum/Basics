/**
 * mutt_addwch - addwch would be provided by an up-to-date curses library
 * @param wc Wide char to display
 * @retval  0 Success
 * @retval -1 Error
 */
int mutt_addwch(wchar_t wc)
{
  char buf[MB_LEN_MAX * 2];
  mbstate_t mbstate;
  size_t n1, n2;

  memset(&mbstate, 0, sizeof(mbstate));
  if (((n1 = wcrtomb(buf, wc, &mbstate)) == (size_t)(-1)) ||
      ((n2 = wcrtomb(buf + n1, 0, &mbstate)) == (size_t)(-1)))
  {
    return -1; /* ERR */
  }
  else
  {
    return addstr(buf);
  }
}