static QList<double> _calcPrettyBreaks( double minimum, double maximum, int classes )
{

  // C++ implementation of R's pretty algorithm
  // Based on code for determining optimal tick placement for statistical graphics
  // from the R statistical programming language.
  // Code ported from R implementation from 'labeling' R package
  //
  // Computes a sequence of about 'classes' equally spaced round values
  // which cover the range of values from 'minimum' to 'maximum'.
  // The values are chosen so that they are 1, 2 or 5 times a power of 10.

  QList<double> breaks;
  if ( classes < 1 )
  {
    breaks.append( maximum );
    return breaks;
  }

  int minimumCount = ( int ) classes / 3;
  double shrink = 0.75;
  double highBias = 1.5;
  double adjustBias = 0.5 + 1.5 * highBias;
  int divisions = classes;
  double h = highBias;
  double cell;
  int U;
  bool small = false;
  double dx = maximum - minimum;

  if ( dx == 0 && maximum == 0 )
  {
    cell = 1.0;
    small = true;
    U = 1;
  }
  else
  {
    cell = qMax( qAbs( minimum ), qAbs( maximum ) );
    if ( adjustBias >= 1.5 * h + 0.5 )
    {
      U = 1 + ( 1.0 / ( 1 + h ) );
    }
    else
    {
      U = 1 + ( 1.5 / ( 1 + adjustBias ) );
    }
    small = dx < ( cell * U * qMax( 1, divisions ) * 1e-07 * 3.0 );
  }

  if ( small )
  {
    if ( cell > 10 )
    {
      cell = 9 + cell / 10;
      cell = cell * shrink;
    }
    if ( minimumCount > 1 )
    {
      cell = cell / minimumCount;
    }
  }
  else
  {
    cell = dx;
    if ( divisions > 1 )
    {
      cell = cell / divisions;
    }
  }
  if ( cell < 20 * 1e-07 )
  {
    cell = 20 * 1e-07;
  }

  double base = pow( 10.0, floor( log10( cell ) ) );
  double unit = base;
  if (( 2 * base ) - cell < h *( cell - unit ) )
  {
    unit = 2.0 * base;
    if (( 5 * base ) - cell < adjustBias *( cell - unit ) )
    {
      unit = 5.0 * base;
      if (( 10.0 * base ) - cell < h *( cell - unit ) )
      {
        unit = 10.0 * base;
      }
    }
  }
  // Maybe used to correct for the epsilon here??
  int start = floor( minimum / unit + 1e-07 );
  int end = ceil( maximum / unit - 1e-07 );

  // Extend the range out beyond the data. Does this ever happen??
  while ( start * unit > minimum + ( 1e-07 * unit ) )
  {
    start = start - 1;
  }
  while ( end * unit < maximum - ( 1e-07 * unit ) )
  {
    end = end + 1;
  }
  QgsDebugMsg( QString( "pretty classes: %1" ).arg( end ) );

  // If we don't have quite enough labels, extend the range out
  // to make more (these labels are beyond the data :( )
  int k = floor( 0.5 + end - start );
  if ( k < minimumCount )
  {
    k = minimumCount - k;
    if ( start >= 0 )
    {
      end = end + k / 2;
      start = start - k / 2 + k % 2;
    }
    else
    {
      start = start - k / 2;
      end = end + k / 2 + k % 2;
    }
    divisions = minimumCount;
  }
  else
  {
    divisions = k;
  }
  double minimumBreak = start * unit;
  //double maximumBreak = end * unit;
  int count = end - start;

  for ( int i = 1; i < count + 1; i++ )
  {
    breaks.append( minimumBreak + i * unit );
  }

  if ( breaks.isEmpty() )
    return breaks;

  if ( breaks.first() < minimum )
  {
    breaks[0] = minimum;
  }
  if ( breaks.last() > maximum )
  {
    breaks[breaks.count()-1] = maximum;
  }

  return breaks;
} // _calcPrettyBreaks