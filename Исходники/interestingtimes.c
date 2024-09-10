void tty_sigreset(int i)
{
  tty_reset();
  _exit(128+i);
}