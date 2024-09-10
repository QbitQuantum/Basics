/** Compare two REAL4 vectors using various different comparison metrics
 */
int
XLALCompareREAL4Vectors ( VectorComparison *result,	///< [out] return comparison results
                          const REAL4Vector *x,		///< [in] first input vector
                          const REAL4Vector *y,		///< [in] second input vector
                          const VectorComparison *tol	///< [in] accepted tolerances on comparisons, or NULL for no check
                          )
{
  XLAL_CHECK ( result != NULL, XLAL_EINVAL );
  XLAL_CHECK ( x != NULL, XLAL_EINVAL );
  XLAL_CHECK ( y != NULL, XLAL_EINVAL );
  XLAL_CHECK ( x->data != NULL, XLAL_EINVAL );
  XLAL_CHECK ( y->data != NULL, XLAL_EINVAL );
  XLAL_CHECK ( x->length > 0, XLAL_EINVAL );
  XLAL_CHECK ( x->length == y->length, XLAL_EINVAL );

  REAL8 x_L1 = 0, x_L2 = 0;
  REAL8 y_L1 = 0, y_L2 = 0;
  REAL8 diff_L1 = 0, diff_L2 = 0;
  REAL8 scalar = 0;

  REAL4 maxAbsx = 0, maxAbsy = 0;
  REAL4 x_atMaxAbsx = 0, y_atMaxAbsx = 0;
  REAL4 x_atMaxAbsy = 0, y_atMaxAbsy = 0;

  UINT4 numSamples = x->length;
  for ( UINT4 i = 0; i < numSamples; i ++ )
    {
      REAL4 x_i = x->data[i];
      REAL4 y_i = y->data[i];
      XLAL_CHECK ( isfinite ( x_i ), XLAL_EFPINVAL, "non-finite element: x(%d) = %g\n", i, x_i );
      XLAL_CHECK ( isfinite ( y_i ), XLAL_EFPINVAL, "non-finite element: y(%d) = %g\n", i, y_i );
      REAL4 xAbs_i = fabs ( x_i );
      REAL4 yAbs_i = fabs ( y_i );

      REAL8 absdiff = fabs ( x_i - y_i );
      diff_L1 += absdiff;
      diff_L2 += SQ(absdiff);

      x_L1 += xAbs_i;
      y_L1 += yAbs_i;
      x_L2 += SQ(xAbs_i);
      y_L2 += SQ(yAbs_i);

      scalar += x_i * y_i;

      if ( xAbs_i > maxAbsx ) {
        maxAbsx = xAbs_i;
        x_atMaxAbsx = x_i;
        y_atMaxAbsx = y_i;
      }
      if ( yAbs_i > maxAbsy ) {
        maxAbsy = yAbs_i;
        x_atMaxAbsy = x_i;
        y_atMaxAbsy = y_i;
      }

    } // for i < numSamples

  // complete L2 norms by taking sqrt
  x_L2 = sqrt ( x_L2 );
  y_L2 = sqrt ( y_L2 );
  diff_L2 = sqrt ( diff_L2 );

  // compute and return comparison results
  result->relErr_L1 = diff_L1 / ( 0.5 * (x_L1 + y_L1 ) );
  result->relErr_L2 = diff_L2 / ( 0.5 * (x_L2 + y_L2 ) );
  REAL8 cosTheta = fmin ( 1, scalar / (x_L2 * y_L2) );
  result->angleV = acos ( cosTheta );
  result->relErr_atMaxAbsx = fRELERR ( x_atMaxAbsx, y_atMaxAbsx );
  result->relErr_atMaxAbsy = fRELERR ( x_atMaxAbsy, y_atMaxAbsy );;

  XLAL_CHECK ( XLALCheckVectorComparisonTolerances ( result, tol ) == XLAL_SUCCESS, XLAL_EFUNC );

  return XLAL_SUCCESS;

} // XLALCompareREAL4Vectors()