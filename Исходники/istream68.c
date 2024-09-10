int istream_putc(istream_t *istream, const int c)
{
  unsigned char byte = c;
  return -(istream_write(istream,&byte,1) != 1);
}