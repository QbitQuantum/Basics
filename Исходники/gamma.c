double tgamma ( double x )
      {
      register int n, parity, i;
      register double y, y1, result, fact, IsItAnInt, z, numerator, 
	                denominator, ysquared, sum; 
      hexdouble OldEnvironment;
    
      FEGETENVD( OldEnvironment.d );               // save environment, set default
      FESETENVD( 0.0 );
	
/*******************************************************************************
*     The next switch will decipher what sort of argument we have. If argument *
*     is SNaN then a QNaN has to be returned and the invalid flag signaled.    * 
*******************************************************************************/

      switch ( __fpclassifyd ( x ) )
            {
            case FP_NAN:
                  x *= 2.0;                  /* quiets NaN */
                  FESETENVD( OldEnvironment.d ); //   restore caller's environment
                  return x;
                  
            case FP_ZERO:
                  OldEnvironment.i.lo |= FE_DIVBYZERO;
                  FESETENVD( OldEnvironment.d );
                  return copysign( Huge.d, x);

             case FP_INFINITE:
                  if ( x > 0.0 )
                        x = Huge.d;
                  else
                        {
                        x = nan ( GAMMA_NAN );
                        OldEnvironment.i.lo |= SET_INVALID;
                        }

                  FESETENVD( OldEnvironment.d );
                  return x;
                  
            default:                  /*      NORMALNUM and DENORMALNUM      */
                  break;
            }
      
      parity = 0;
      fact = 1.0;
      n = 0;
      y = x;

/*******************************************************************************
*     The argument is negative.                                                *
*******************************************************************************/

      if ( y <= 0.0 )
            {
            y = - x;
			if ( y < MinimumX )
			      {
                  OldEnvironment.i.lo |= FE_OVERFLOW;
                  FESETENVD( OldEnvironment.d );
                  return MinusHuge.d;
				  }
            y1 = trunc ( y );
            IsItAnInt = y - y1;
            if ( IsItAnInt != 0.0 )                   /* is it an integer?   */
                  {                                   /* is it odd or even?  */
                  if ( y1 != trunc ( y1 * 0.5 ) * 2.0 ) parity = 1;
                  fact = - pi / sin ( pi * IsItAnInt );
                  y += 1.0;
                  }
            else
                  {
                  OldEnvironment.i.lo |= SET_INVALID;
                  FESETENVD( OldEnvironment.d );
                  return nan ( GAMMA_NAN );
                  }
            }

/*******************************************************************************
*     The argument is positive.                                                *
*******************************************************************************/

     if ( y < eps )                         /* argument is less than epsilon. */
            {
            if ( y >= MinimumX )          /* x is in [MinimumX,eps].          */
                  result = 1.0 / y;
            else                          /* othewise, x is in [0,MinimumX).  */
                  {
                  OldEnvironment.i.lo |= FE_OVERFLOW;
                  FESETENVD( OldEnvironment.d );
                  return Huge.d;
                  }
            }
      else if ( y < 12.0 )                 /* argument x is eps < x < 12.0.  */
            {
            y1 = y;
            if ( y < 1.0 )                 /* x is in (eps, 1.0).            */
                  {
                  z = y;
                  y += 1.0;
                  }
            else                           /* x is in [1.0,12.0].            */
                  {
                  n = ( int ) y - 1;
                  y -= ( double ) n;
                  z = y - 1.0;
                  }
            numerator = 0.0;
            denominator = 1.0;
            for ( i = 0; i < 8; i++ )
                  {
                  numerator = ( numerator + p[i] ) * z;
                  denominator = denominator * z + q[i];
                  }
            result = numerator / denominator + 1.0;
            if ( y1 < y )
                  result /= y1;
            else if ( y1 > y )
                  {
                  for ( i = 0; i < n; i++ )
                        {
                        result *= y;
                        y += 1.0;
                        }
                  }
            }
      else
            {
            if ( x <= xbig )
                  {
                  ysquared = y * y;
                  sum = c[6];
                  for ( i = 0; i < 6; i++ )
                        sum = sum / ysquared + c[i];
                  sum = sum / y - y + LogSqrt2pi;
                  sum += ( y - 0.5 ) * log ( y );
                  result = exp ( sum );
                  }
            else
                  {
                  OldEnvironment.i.lo |= FE_OVERFLOW;
                  FESETENVD( OldEnvironment.d );         //   restore caller's environment
                  return Huge.d;
                  }
            }
      if ( parity ) result = - result;
      if ( fact != 1.0 ) result = fact / result;
      FESETENVD( OldEnvironment.d );         //   restore caller's environment
      return result;
      }