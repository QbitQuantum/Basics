/*
 * TermInfo.tiocswinsz(io, row, col)
 *
 * TermInfo.tiocgwinsz update the screen size information of the terminal refered by io,
 * using TIOCSWINSZ ioctl.
 *
 * It returns nil.
 */
static VALUE
rt_tiocswinsz(VALUE self, VALUE io, VALUE row, VALUE col)
{
#ifdef TIOCSWINSZ
  rb_io_t *fptr;
  struct winsize sz;
  int ret;

  GetOpenFile(io, fptr);

  sz.ws_row = NUM2INT(row);
  sz.ws_col = NUM2INT(col);

  ret = ioctl(FILENO(fptr), TIOCSWINSZ, &sz);
  if (ret == -1) rb_raise(rb_eIOError, "TIOCSWINSZ failed");

  return Qnil;
#else
  rb_notimplement();
#endif
}