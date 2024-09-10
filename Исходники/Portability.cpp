char* itoa(int value, char*  str, int radix)
{
  int  rem = 0;
  int  pos = 0;
  char ch  = '!' ;
  do
  {
    rem    = value % radix ;
    value /= radix;
    if ( 16 == radix )
    {
      if( rem >= 10 && rem <= 15 )
      {
        switch( rem )
        {
          case 10:
            ch = 'a' ;
            break;
          case 11:
            ch ='b' ;
            break;
          case 12:
            ch = 'c' ;
            break;
          case 13:
            ch ='d' ;
            break;
          case 14:
            ch = 'e' ;
            break;
          case 15:
            ch ='f' ;
            break;
        }
      }
    }
    if( '!' == ch )
    {
      str[pos++] = (char) ( rem + 0x30 );
    }
    else
    {
      str[pos++] = ch ;
    }
  }
  while( value != 0 );
  str[pos] = '\0' ;
  return strrev(str);
}