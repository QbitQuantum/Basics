void upsampleArray( const pfs::Array2D *in, pfs::Array2D *out, ResampleFilter *filter )
{
  float dx = (float)in->getCols() / (float)out->getCols();
  float dy = (float)in->getRows() / (float)out->getRows();

  float pad;
  
  float filterSamplingX = max( modff( dx, &pad ), 0.01f );
  float filterSamplingY = max( modff( dy, &pad ), 0.01f );

  const int outRows = out->getRows();
  const int outCols = out->getCols();

  const float inRows = (float)in->getRows();
  const float inCols = (float)in->getCols();

  const float filterSize = filter->getSize();

// TODO: possible optimization: create lookup table for the filter
  
  float sx, sy;
  int x, y;
  for( y = 0, sy = -0.5f + dy/2; y < outRows; y++, sy += dy )
    for( x = 0, sx = -0.5f + dx/2; x < outCols; x++, sx += dx ) {

      float pixVal = 0;
      float weight = 0;
      
      for( float ix = max( 0, ceilf( sx-filterSize ) ); ix <= min( floorf(sx+filterSize), inCols-1 ); ix++ )
        for( float iy = max( 0, ceilf( sy-filterSize ) ); iy <= min( floorf( sy+filterSize), inRows-1 ); iy++ ) {
          float fx = fabs( sx - ix );
          float fy = fabs( sy - iy );

          const float fval = filter->getValue( fx )*filter->getValue( fy );
          
          pixVal += (*in)( (int)ix, (int)iy ) * fval;
          weight += fval;
        }

      if( weight == 0 ) {
        fprintf( stderr, "%g %g %g %g\n", sx, sy, dx, dy );
      }    
//      assert( weight != 0 );
      (*out)(x,y) = pixVal / weight;

    } 
}