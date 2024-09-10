int main( int argc, char* argv[] ) {

#if defined(_WIN32) && !defined(__CYGWIN__)
 if ( _setmode( _fileno( stdout ), _O_BINARY ) == -1 ) {
    printf( "Cannot set stdout to binary mode.  Exiting." );
    return -1;
 }
#endif

  char*     userfilename = NULL;
  int       user_capk    = -1;
  double    user_centerx = 0.0;
  double    user_centery = 0.0;
  int       user_centeroverride = 0;
  double    user_julia_r = 0.0;
  double    user_julia_i = 0.0;
  int       MakeJuliaSet = 0;
  long      user_resolx = 0.0;
  long      user_resoly = 0.0;
  int       user_resolutionoverride = 0;
  double    user_zoomlevel = -1.0;

  long i;
  for ( i = 1; i < argc; ) {
    int ishyphen = argv[i][0] == '-';
    long len = strlen( argv[i] );
    long nextlen = (i+1) < argc ? strlen( argv[i+1] ) : -1;

    int argsprocessed = 0;
    if ( ishyphen && len > 1 )
      argsprocessed = 1;

    if ( argsprocessed >= 1 ) {
      char useroption = argv[i][1];
      char* optionvalue = NULL;
      if ( len >= 3 )
        optionvalue = &argv[i][2];

      switch ( useroption ) {
       case 'c':  // center point  (x,y)
        if ( optionvalue == NULL && nextlen > 0 ) {
          optionvalue = argv[i+1];
          argsprocessed = 2;
        }
        if ( optionvalue != NULL )
          user_centeroverride = !Get2Tuple( optionvalue, &user_centerx, &user_centery );
        break;
       case 'h':
        printusage();
        return 0;
        break;
       case 'j':  // julia set constant value (the real part and imaginary part)
        if ( optionvalue == NULL && nextlen > 0 ) {
          optionvalue = argv[i+1];
          argsprocessed = 2;
        }
        if ( optionvalue != NULL )
          MakeJuliaSet = !Get2Tuple( optionvalue, &user_julia_r, &user_julia_i );
        break;
       case 'm':  // maximum number of iterations per pixel
        if ( optionvalue == NULL && nextlen > 0 ) {
          optionvalue = argv[i+1];
          argsprocessed = 2;
        }
        if ( optionvalue != NULL )
          user_capk = abs(atoi( optionvalue ));
        break;
       case 'o':  // output file name
        if ( optionvalue == NULL && nextlen > 0 ) {
          optionvalue = argv[i+1];
          argsprocessed = 2;
        }
        if ( optionvalue != NULL )
          userfilename = strdup( optionvalue );
        break;
       case 'r':  // image resolution
        if ( optionvalue == NULL && nextlen > 0 ) {
          optionvalue = argv[i+1];
          argsprocessed = 2;
        }
        if ( optionvalue != NULL )
          user_resolutionoverride = !Get2Tuple( optionvalue, &user_resolx, &user_resoly );
        break;
       case 'v':
        printf( "fractals version %s\n", VersionStr );
        return 0;
        break;
       case 'z':
        if ( optionvalue == NULL && nextlen > 0 ) {
          optionvalue = argv[i+1];
          argsprocessed = 2;
        }
        if ( optionvalue != NULL )
          user_zoomlevel = fabs(atof( optionvalue ));
        break;
       default:
        break;
      }
    }

    if ( argsprocessed == 2 )
      i += 2;
    else
      i++;
  }

  double centerx = 0.0;
  double centery = 0.0;
  if ( !MakeJuliaSet )  // ie. Make the Mandelbrot Set
    centerx = -0.75;
  if ( user_centeroverride ) {
    centerx = user_centerx;
    centery = user_centery;
  }

  double c_r = 0.0;
  double c_i = 0.0;
  if ( MakeJuliaSet ) {
    c_r = user_julia_r;
    c_i = user_julia_i;
  }

  int capk = 2048;
  if ( user_capk > 0 && user_capk < 10000000 )
    capk = user_capk;

  FILE* fpout = stdout;
  if ( userfilename != NULL ) {
    FILE* fdtest = fopen( userfilename, "r" );
    if ( fdtest != NULL ) {
      printf("Output file \"%s\" already exists.  Refusing to overwrite.  Exiting.\n\n", userfilename );
      fclose( fdtest );
      free( userfilename );
      return -1;
    }
    fpout = fopen( userfilename, "wb" );
    if ( fpout == NULL ) {
      printf("Error: Could not open file \"%s\" for write.  Exiting.\n\n", userfilename );
      free( userfilename );
      return -1;
    }
  }

  long resolx = 1024;  // horizontal resolution in pixels
  long resoly = 768;   // vertical resolution in pixels
  if ( user_resolutionoverride ) {
    resolx = user_resolx;
    resoly = user_resoly;
  }

  double zoomlevel = 1.0;  // zoomlevel of 1.0 arbitrarily defined to be an x-width of 3.1.
  if ( user_zoomlevel > 0.00001 && user_zoomlevel < 10000000.0 )
    zoomlevel = user_zoomlevel;
  double fulldx = 3.1 / zoomlevel;
  double fulldy = (3.1 / zoomlevel) * ((double)resoly /(double)resolx);

  double pixelwidth = fulldx/(double)resolx;  // Could of just as easily been fulldy/(double)resoly
  double halfpixel = pixelwidth / 2.0;

  double xmin = centerx - fulldx / 2.0;
  double xminplushalf = xmin + halfpixel; // like to use the middles of pixels
  double ymax = centery + fulldy / 2.0;
  double ymaxlesshalf = ymax - halfpixel; // like to use the middles of pixels


  const double m  = 100.0;  // min norm to be considered an escapee


  struct pixel holdpal[256];
  initpal( holdpal );

  fprintf( fpout, "P6" );
  fwrite( CRLF, 1, 2, fpout );

  fprintf( fpout, "%ld %ld", resolx, resoly );
  fwrite( CRLF, 1, 2, fpout );

  fprintf( fpout, "255" );
  fwrite( CRLF, 1, 2, fpout );

  long x,y;
  for ( y = 0; y < resoly; y++ ) {
    for ( x = 0; x < resolx; x++ ) {
      double z_r = 0.0;
      double z_i = 0.0;

      if ( MakeJuliaSet ) {
        z_r = xminplushalf + x * pixelwidth;
        z_i = ymaxlesshalf - y * pixelwidth;
      }
      else {  // Make the Mandelbrot Set
        c_r = xminplushalf + x * pixelwidth;
        c_i = ymaxlesshalf - y * pixelwidth;
      }

      int k = -1;
      double norm = 0.0;

      double z_r_save = z_r;
      while ( norm < m && k < capk ) {  // repeatedly iterating z = z^2 + c  where z & c are complex numbers
        z_r_save = z_r;
        z_r = z_r_save * z_r_save - z_i * z_i + c_r;
        z_i = 2 * z_r_save * z_i + c_i;
        k++;
        norm = z_r * z_r + z_i * z_i;
      }

      if ( k == capk )
          k = 255;
      else
          k %= 254;

      fwrite( &holdpal[k], 1, 3, fpout );
    }
  }

  if ( fpout != stdout ) {
    fclose(fpout);
    fpout = NULL;
  }

  if ( userfilename != NULL ) {
    free( userfilename );
    userfilename = NULL;
  }

  return 0;
}