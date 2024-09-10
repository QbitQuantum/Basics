BOOL MYRTLEXP QnxCmpFile( char *f1, char *f2, int len )
  {  BOOL  b1,b2;
     static struct _osinfo oi;
     static char   name[16] = "";
     static int    nmlen;
//CCurrent machine name
    if ( !name[0] ) {
      qnx_osinfo( 0, &oi );
      Sprintf( name,"//%ld",oi.nodename );
      nmlen = strLen( name );
    }
//Cmp not paths
    if ( !f1 || !f2 || f1[0] != '/' || f2[0] != '/' )
      if ( len < 0 )
        return StrCmp(f1,f2) == 0;
       else
        return StrNCmp(f1,f2,len) == 0;
//Paths cmp
    b1 = (f1[0] == '/' && f1[1] == '/');
    b2 = (f2[0] == '/' && f2[1] == '/');

    if ( b1 != b2 ) {
      if ( !b1 ) {
        if ( StrNCmp(name,f2,nmlen) != 0 ) return FALSE;
        if ( len >= 0 && strLen(f2) == len ) len -= nmlen;
        f2 += nmlen;
      }
      if ( !b2 ) {
        if ( StrNCmp(name,f1,nmlen) != 0 ) return FALSE;
        if ( len >= 0 && strLen(f1) == len ) len -= nmlen;
        f1 += nmlen;
      }
    }
    if ( len < 0 )
      return StrCmp(f1,f2) == 0;
     else
      return StrNCmp(f1,f2,len) == 0;
}