str
wide_str_t::to_utf8 () const
{
  static size_t utf8_char_width = 6;
  str ret;
  if (!_buf) { /*noop */ } 
  else if (_len == 0) { ret = ""; }
  else {
    mbstate_t state;
    memset (&state, 0, sizeof (state));
    size_t len = _len * utf8_char_width;
    mstr m (len);
    const wchar_t *in = _buf->base ();
    ssize_t nbytes = wcsrtombs (m.cstr (), &in, len, &state);
    if (nbytes >= 0) {

      // should have consumed all bytes; if not '6' above is wrong!!
      assert (!in);

      m.setlen (nbytes);
      ret = m;
    }
  }
  return ret;
}