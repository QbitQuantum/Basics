INProc::INProc( CONSTSTR nm,CONSTSTR s,... )
    : Name(nm)
  {  va_list  ap;
     char     str[500];
     DWORD    err = FIO_ERRORN;

    SNprintf( str,sizeof(str), "%*c%s(", Counter*2,' ',nm );

    if ( s ) {
      va_start( ap,s );
        StrCat( str,MessageV(s,ap),sizeof(str) );
      va_end(ap);
    }
    StrCat( str,") {",sizeof(str) );
    FILELog( str );

    Counter++;
    FIO_SETERRORN( err );
}