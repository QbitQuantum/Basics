static int GetStatFromRAR(char *rar_line, char *name, struct stat *stat)
{
  char *t, *old;
  int  id;
  struct tm tm_struct;


  (void) memset( stat, 0, sizeof( struct stat ) );

  stat->st_nlink = 1;

  t = Strtok_r( rar_line, " \t", &old ); if( t == NULL ) return( -1 );

  /* Dateiname */
  /*-----------*/

  (void) strcpy( name, t );
  t = Strtok_r( NULL, " \t", &old ); if( t == NULL ) return( -1 );

  /* Dateilaenge */
  /*-------------*/

  if( !isdigit( *t ) ) return( -1 );
  stat->st_size = AtoLL( t );
  t = Strtok_r( NULL, " \t", &old ); if( t == NULL ) return( -1 );

  /* Packed */
  /*--------*/

  t = Strtok_r( NULL, " \t", &old ); if( t == NULL ) return( -1 );

  /* Ratio */
  /*-------*/

  t = Strtok_r( NULL, " \t", &old ); if( t == NULL ) return( -1 );

  /* M-Datum */
  /*---------*/

  if(strlen(t) == 8) {
    t[2] = t[5] = '\0';    
    tm_struct.tm_mday = atoi( &t[0] );
    tm_struct.tm_mon  = atoi( &t[3] );
    tm_struct.tm_year = atoi( &t[6] );

    if(tm_struct.tm_year < 70)
       tm_struct.tm_year += 100;
  }

  t = Strtok_r( NULL, " \t", &old ); if( t == NULL ) return( -1 );

  /* M-time */
  /*--------*/

  if(strlen(t) == 5) {
    t[2] = '\0';
    tm_struct.tm_hour = atoi( &t[0] );
    tm_struct.tm_min  = atoi( &t[2] );
  }

  tm_struct.tm_sec = 0;
  tm_struct.tm_isdst = -1;

  stat->st_atime = 0;
  stat->st_ctime = 0;

  stat->st_mtime = Mktime( &tm_struct );

  t = Strtok_r( NULL, " \t", &old ); if( t == NULL ) return( -1 );

  /* Attributes */
  /*------------*/

  stat->st_mode = S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  /* Owner */
  /*-------*/

  id = getuid();
  if( id == -1 ) id = atoi( t );
  stat->st_uid = (unsigned) id;

  /* Group */
  /*-------*/

  id = getgid();
  stat->st_gid = (unsigned) id;
  
  return( 0 );
}