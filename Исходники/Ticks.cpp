void ticksize_command(wchar_t *arg)
{
  if(*arg!='\0') {
    if(iswdigit(*arg)) {
      tick_size=_wtoi(arg);
      dwTime0=GetTickCount()/1000;
      tintin_puts2(rs::rs(1180));        
    }
  }
  else
    tintin_puts2(rs::rs(1181));
}     