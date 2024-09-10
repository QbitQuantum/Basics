int main( int argc, char *argv[] )
{
  char out_filename[256];
  
  if( argc != 4 )
  {
    fprintf( stderr, "closeshp poly_shape arc_shape output_shape\n" );
    return 1;
  }
  char *poly_file = argv[1];
  char *arc_file = argv[2];
  char *out_file = argv[3];

  struct source poly, arc, simplified;
  memset( &poly, 0, sizeof(poly) );
  memset( &arc, 0, sizeof(arc) );
  memset( &simplified, 0, sizeof(simplified) );
  poly.in_memory = arc.in_memory = 0;
  simplified.in_memory = 1;

  /* open shapefiles and dbf files */
  if( SourceOpen( &poly, poly_file, SHPT_POLYGON ) )
    return 1;
  if( SourceOpen( &arc, arc_file, SHPT_ARC ) )
    return 1;

  sprintf( out_filename, "%s_p", out_file );
  shp_out = SHPCreate( out_filename, SHPT_POLYGON );
  if( !shp_out )
  {
    fprintf( stderr, "Couldn't create shapefile '%s': %s\n", out_file, strerror(errno));
    return 1;
  }
  
  dbf_out = DBFCreate( out_filename );
  if( !dbf_out )
  {
    fprintf( stderr, "Couldn't create DBF '%s': %s\n", out_file, strerror(errno));
    return 1;
  }
//  DBFAddField( dbf_out, "way_id", FTInteger, 11, 0 );
//  DBFAddField( dbf_out, "orientation", FTInteger, 1, 0 );
  DBFAddField( dbf_out, "error", FTInteger, 1, 0 );
  DBFAddField( dbf_out, "tile_x", FTInteger, 4, 0 );
  DBFAddField( dbf_out, "tile_y", FTInteger, 4, 0 );

  /* Initialise node arrays */
  v_x = malloc( MAX_NODES * sizeof(double) );
  v_y = malloc( MAX_NODES * sizeof(double) );
  
  if( !v_x || !v_y )
  {
    fprintf( stderr, "Couldn't allocate memory for nodes\n" );
    return 1;
  }
  /* Setup state */
  struct state state;
  memset( &state, 0, sizeof(state) );
  ResizeSubareas(&state, INIT_MAX_SUBAREAS);
  
  // Temporary file for simplified shapes
  {
      // Make the file and open it
      char filename[32];
      sprintf( filename, "tmp_coastline_%d", getpid() );
      simplified.shp = SHPCreate( filename, SHPT_ARC );
      if( !simplified.shp )
      {
          fprintf( stderr, "Couldn't open temporary shapefile: %s\n", strerror(errno) );
          return 1;
      }
      // And now unlink them so they're cleaned up when we die
      int len = strlen( filename );
      strcpy( filename+len, ".shp" );
      unlink(filename);
      strcpy( filename+len, ".shx" );
      unlink(filename);
      
      // Setup the bitmap while creating the simplified polygons
      InitBitmap( &arc, &simplified );
      InitBitmap( &poly, &simplified );
      
      // And index the simplified polygons
      simplified.shx = SHPCreateTree( simplified.shp, 2, 10, NULL, NULL );
      if( !simplified.shx )
      {
          fprintf( stderr, "Couldn't build temporary shapetree\n" );
          return 1;
      }
      SHPGetInfo( simplified.shp, &simplified.shape_count, NULL, NULL, NULL );
      simplified.shapes = calloc( simplified.shape_count, sizeof(SHPObject*) );
  }
  /* Split coastlines into arcs no longer than MAX_NODES_PER_ARC long */
  sprintf( out_filename, "%s_i", out_file );
  SplitCoastlines( &poly, &arc, out_filename );

#if !TEST  
  for( int i=0; i<DIVISIONS; i++ )
    for( int j=0; j<DIVISIONS; j++ )  //Divide the world into mercator blocks approx 100km x 100km
#else
  for( int i=204; i<=204; i++ )
    for( int j=248; j<=248; j++ )  //Divide the world into mercator blocks approx 100km x 100km
#endif
    {
      state.x = i;
      state.y = j;
      
      double left   = -MERC_MAX + (i*MERC_BLOCK) - TILE_OVERLAP;
      double right  = -MERC_MAX + ((i+1)*MERC_BLOCK) + TILE_OVERLAP;
      double bottom = -MERC_MAX + (j*MERC_BLOCK) - TILE_OVERLAP;
      double top    = -MERC_MAX + ((j+1)*MERC_BLOCK) + TILE_OVERLAP;
      
      if( left  < -MERC_MAX ) left  = -MERC_MAX;
      if( right > +MERC_MAX ) right = +MERC_MAX;
      
      state.lb[0] = left;
      state.lb[1] = bottom;
      state.rt[0] = right;
      state.rt[1] = top;
      
      if(isatty(STDERR_FILENO))
//        fprintf( stderr, "\rProcessing (%d,%d)  (%.2f,%.2f)-(%.2f,%.2f)   ", i, j, left, bottom, right, top );
        fprintf( stderr, "\rProcessing (%d,%d)  (%.2f,%.2f)-(%.2f,%.2f)   ", i, j, state.lb[0], state.lb[1], state.rt[0], state.rt[1] );
      state.seg_count = 0;
      state.subarea_count = 0;
      state.subarea_nodecount = 0;
      state.enclosed = 0;
      
      // Optimisation: if we have determined nothing enters the tile, we can used the simplified tiles
      // Basically, we only need to test for enclosure
      if( check_tile( state.x, state.y ) )
      {
        Process( &state, &poly, 1 );
        Process( &state, &arc,  0 );
      }
      else
        Process( &state, &simplified, 0 );

      OutputSegs( &state );
    }
    
  free( state.sub_areas );
  free( simplified.shapes );
  SHPDestroyTree( poly.shx );
  SHPDestroyTree( arc.shx );
  SHPDestroyTree( simplified.shx );
  DBFClose( poly.dbf );
  DBFClose( arc.dbf );
  DBFClose( dbf_out );
  SHPClose( poly.shp );
  SHPClose( arc.shp );
  SHPClose( simplified.shp );
  SHPClose( shp_out );
  
  printf("\n");
  return 0;
}