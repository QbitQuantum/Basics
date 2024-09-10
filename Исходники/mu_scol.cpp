int MYRTLEXP StrColCount( CONSTSTR str,CONSTSTR seps )
  {  int res = 1;

     if ( !str || !seps || !str[0] || !seps[0] ) return 0;

     for ( int n = 0; str[n]; n++ )
       if ( StrChr(seps,str[n]) != NULL )
         res++;
  return res;
}