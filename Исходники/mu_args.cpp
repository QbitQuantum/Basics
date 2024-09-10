void MYRTLEXP CTArgInit( int argc, char **argv,BOOL CaseSensitive )
  {
    DeleteArgs();
    CT_CaseSensitive = CaseSensitive;
    CT_SelfArgs      = TRUE;

    CT_argc = argc;
    CT_argv = new pchar[ CT_argc+1 ];
    int n;

    if ( StrChr(argv[0],SLASH_CHAR) == NULL )
      CT_argv[0] = StrDup( MakePathName(GetCurDir(),argv[0]).Text() );
     else
      CT_argv[0] = StrDup( argv[0] );

    for( n = 1; n < CT_argc; n++ )
      CT_argv[n] = StrDup( argv[n] );

    CT_argv[n] = NULL;
}