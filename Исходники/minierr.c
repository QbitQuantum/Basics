void
minierr_vdie( int line, const char *func, const char *file, int wraplines, mas_minierr_type_t et, int fexit, unsigned flags, const char *sid, const char *fmt,
              va_list args )
{
  char *pf = strrchr( file, '/' );
  char buffer[1024] = "";
  size_t prefwidth = 10;
  int a = 0, b = 0;

  if ( !( disabled_flags & ( 1UL << et ) ) )
  {
    if ( pf )
      pf++;
#define MAS_MIER_PRN(...) { size_t l=strlen( buffer ); snprintf( buffer + l, sizeof( buffer ) - l, __VA_ARGS__); }

/* MAS_MIER_PRN( "[%ld] ", prefwidth ); */
/* MAS_MIER_PRN( "[%lx] %x %x", ( long ) flags, MAS_MIER_FLAG_EXIT, MAS_MIER_FLAG_SLEEP ); */
    if ( flags &
         ( MAS_MIER_FLAG_EXIT | MAS_MIER_FLAG_ASSERT | MAS_MIER_FLAG_LINE | MAS_MIER_FLAG_FUNC | MAS_MIER_FLAG_FILE | MAS_MIER_FLAG_COLPREF ) )
    {
      a = 33;
      if ( flags & ( MAS_MIER_FLAG_EXIT | MAS_MIER_FLAG_ASSERT ) )
        b = 41;
      else if ( flags & MAS_MIER_FLAG_COLPREF )
        b = 46;
      else
        b = 44;
    }
    if ( a || b )
      MAS_MIER_PRN( "\x1b[0;1;7;%d;%dm", a, b );
    MAS_MIER_PRN( "-=%4s=-", sid ? sid : ( fexit ? "DIE" : "WARN" ) );
#if 1
    if ( flags & ( MAS_MIER_FLAG_EXIT | MAS_MIER_FLAG_ASSERT | MAS_MIER_FLAG_LINE | MAS_MIER_FLAG_FUNC | MAS_MIER_FLAG_FILE ) )
    {
      if ( a || b )
      {
        a = 49;
        b = 36;
      }
      if ( a || b )
        MAS_MIER_PRN( "\x1b[0;1;%d;%dm", a, b );
    }
#endif
    if ( flags & MAS_MIER_FLAG_FUNC )
    {
      prefwidth += 43;
      MAS_MIER_PRN( "%s( )", func );
    }
    if ( flags & MAS_MIER_FLAG_FILE )
    {
      prefwidth += 43;
      MAS_MIER_PRN( " @ %s", pf );
    }
    if ( flags & MAS_MIER_FLAG_LINE )
    {
      prefwidth += 5;
      MAS_MIER_PRN( ":%d ", line );
    }
    if ( a || b )
      MAS_MIER_PRN( "\x1b[%dm", 0 );
    {
      size_t len = strlen( buffer );
      char *p = buffer + len;

    /* *p++ = '{'; */
    /* justify: */
      while ( p && len < prefwidth && len < sizeof( buffer ) - 4 )
      {
        *p++ = '.';
        len++;
      }
    /* *p++ = '}'; */
      *p = 0;
    }
    if ( flags & ( MAS_MIER_FLAG_LINE | MAS_MIER_FLAG_FUNC | MAS_MIER_FLAG_FILE ) )
      MAS_MIER_PRN( " --" );
    MAS_MIER_PRN( " " );
    for (int i=0;i<wraplines;i++)fputs( "\n", stderr );
    fputs( buffer, stderr );
/* fprintf( stderr, "%-50s", buffer ); */
    vfprintf( stderr, fmt, args );
//  fprintf( stderr, "\n" );
    for (int i=0;i<wraplines+1;i++)fputs( "\n", stderr );

#ifdef MAS_TRACEMEM
    if ( flags & MAS_MIER_FLAG_EXIT )
    {
      extern int mas_mem_disable_print_usage __attribute__ ( ( weak ) );

      if ( &mas_mem_disable_print_usage )
        mas_mem_disable_print_usage = 1;
    }
#endif

    if ( flags & MAS_MIER_FLAG_SLEEP )
      sleep( 5 );
    if ( flags & MAS_MIER_FLAG_ASSERT )
      assert( 0 );
    if ( flags & MAS_MIER_FLAG_EXIT )
      exit( fexit );
  }
}