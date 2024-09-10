string int2str(unsigned int val)
{
  char buffer[64] = {0};
  int i=62;
  lldiv_t d;

  d.quot = val;
  do{
    d = lldiv(d.quot,10);
    buffer[i] = _int2str_lookup[d.rem];
  }while(--i && d.quot);

  return string((char*)(buffer+i+1));
}