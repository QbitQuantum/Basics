static int cell_draw( char *name,
                      char *mapset,
                      struct Colors *colors,
                      RASTER_MAP_TYPE data_type )
{
  int cellfile;
  void *xarray;
  int row;
  int ncols, nrows;
  static unsigned char *red, *grn, *blu, *set;
  int i;
  void *ptr;
  int big_endian;
  long one = 1;
  FILE *fo;

  big_endian = !( *(( char * )( &one ) ) );

  ncols = G_window_cols();
  nrows = G_window_rows();

  /* Make sure map is available */
  if (( cellfile = G_open_cell_old( name, mapset ) ) == -1 )
    G_fatal_error(( "Unable to open raster map <%s>" ), name );

  /* Allocate space for cell buffer */
  xarray = G_allocate_raster_buf( data_type );
  red = G_malloc( ncols );
  grn = G_malloc( ncols );
  blu = G_malloc( ncols );
  set = G_malloc( ncols );

  /* some buggy C libraries require BOTH setmode() and fdopen(bin) */
#ifdef WIN32
  if ( _setmode( _fileno( stdout ), _O_BINARY ) == -1 )
    G_fatal_error( "Cannot set stdout mode" );
#endif
  // Unfortunately this is not sufficient on Windows to switch stdout to binary mode
  fo = fdopen( fileno( stdout ), "wb" );

  /* loop for array rows */
  for ( row = 0; row < nrows; row++ )
  {
    G_get_raster_row( cellfile, xarray, row, data_type );
    ptr = xarray;

    G_lookup_raster_colors( xarray, red, grn, blu, set, ncols, colors,
                            data_type );

    for ( i = 0; i < ncols; i++ )
    {
      unsigned char alpha = 255;
      if ( G_is_null_value( ptr, data_type ) )
      {
        alpha = 0;
      }
      ptr = G_incr_void_ptr( ptr, G_raster_size( data_type ) );


      // We need data suitable for QImage 32-bpp
      // the data are stored in QImage as QRgb which is unsigned int.
      // Because it depends on byte order of the platform we have to
      // consider byte order (well, middle endian ignored)
      if ( big_endian )
      {
        // I have never tested this
        fprintf( fo, "%c%c%c%c", alpha, red[i], grn[i], blu[i] );
      }
      else
      {
        fprintf( fo, "%c%c%c%c", blu[i], grn[i], red[i], alpha );
      }
    }
  }

  G_close_cell( cellfile );
  return ( 0 );
}