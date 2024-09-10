  void readmaP( FILE *file, maP *map, texturearraY<BYTE> *Ta ) {
      char str[1024], str2[1024], current_dir[1024], filename[256];
	  long l;


      readstrinG( file, &str[0] );
      do {
          readstrinG( file, &str[0] );

          // BITMAP
		  if( strcmp( "*BITMAP", str ) == 0 ) {
			  readstrinG_( file, &str[0] );

			  Ta->inserT( -1, NULL );
			  parsefilenamE( str, &filename[0] );
			  getcurrentdiR( &current_dir[0], sizeof( current_dir ) );
			  sprintf( str2, "%s\\%s", current_dir, filename );
			  if( loadtgA( str2, &Ta->elem[Ta->num-1] ) || loadtgA( str, &Ta->elem[Ta->num-1] ) ) map->lpT = &Ta->elem[Ta->num-1]; else {
				  map->lpT = NULL;

				  sprintf( str2, "Error: Texture \"%s\" not loaded!", str );
			  	  MessageBoxExA( NULL, str2, NULL, MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND | MB_TOPMOST, 0 );
			  }
		  } else
          // UVW_U_OFFSET
		  if( strcmp( "*UVW_U_OFFSET", str ) == 0 ) {
			  map->offset.x = readfloaT( file );
		  } else
          // UVW_V_OFFSET
		  if( strcmp( "*UVW_V_OFFSET", str ) == 0 ) {
			  map->offset.y = readfloaT( file );
		  } else
          // UVW_U_TILING
		  if( strcmp( "*UVW_U_TILING", str ) == 0 ) {
			  map->tiling.x = readfloaT( file );
		  } else
          // UVW_V_TILING
		  if( strcmp( "*UVW_V_TILING", str ) == 0 ) {
			  map->tiling.y = readfloaT( file );
		  } else
		  //...
          if( strcmp( "{", str ) == 0 ) {
			  l = 1;
			  do { 
				  readstrinG( file, &str[0] ); 
				  if( strcmp( "}", str ) == 0 ) l--; else if( strcmp( "{", str ) == 0 ) l++;
			  } while( l > 0 );
              str[0] = '/x0';
          }
      } while( strcmp( "}", str ) != 0 );
  }