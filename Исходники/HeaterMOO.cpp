void HeaterMOO::fillImage ( double** img ) {
  uint32_t h = getH ();
  uint32_t w = getW ();
  Calibreurs calibreur ( 0, 1, 0.7, 0 );
#pragma omp parallel for if ( _omp )
  for ( size_t i = 1; i <= w; i++ ) {
    for ( size_t j = 1; j <= h; j++ ) {
      double temperature = img[i - 1][j - 1];
      float hue = calibreur.calibrate ( temperature );
      setHue ( i, j, hue );
    }
  }
}