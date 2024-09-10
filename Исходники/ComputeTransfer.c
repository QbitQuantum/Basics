/** UNDOCUMENTED */
void
LALResponseConvert(
    LALStatus               *status,
    COMPLEX8FrequencySeries *output,
    COMPLEX8FrequencySeries *input
    )
{
  LALUnit unitOne;
  LALUnit unitTwo;
  UINT4 i;
  INT4 inv;
  INT4 fac;
  INT4 bad;

  INITSTATUS(status);
  ATTATCHSTATUSPTR( status );

  output->epoch = input->epoch;

  /*
   * Interpolate to requested frequencies.
   * Just do linear interpolation of real and imag components.
   */
  for ( i = 0; i < output->data->length; ++i )
  {
    REAL4 x;
    UINT4 j;
    x = i * output->deltaF / input->deltaF;
    j = floor( x );
    if ( j > input->data->length - 2 )
      j = input->data->length - 2;
    x -= j;
    output->data->data[i] = input->data->data[j]
      + x * ( input->data->data[j+1] - input->data->data[j] );
  }


  /*
   * Use output units to figure out:
   *   1. Whether we want strain/ct or ct/strain
   *   2. Overall (power of ten) factor to apply.
   */

  /* determine if units need to be inverted or not (or if they are bad) */
  XLALUnitNormalize( &output->sampleUnits );
  XLALUnitNormalize( &input->sampleUnits );
  unitOne = output->sampleUnits;
  unitTwo = input->sampleUnits;

  bad = 0;
  inv = -1;
  for ( i = 0; i < LALNumUnits; ++i )
  {
    if ( unitOne.unitDenominatorMinusOne[i] != unitTwo.unitDenominatorMinusOne[i] )
    {
      bad = 1;
      break;
    }
    if ( unitOne.unitNumerator[i] == unitTwo.unitNumerator[i] )
    {
      if ( unitOne.unitNumerator[i] ) /* if this unit exists */
      {
        inv = 0; /* we don't need to invert */
        if ( inv == 1 ) /* error: some units need to be inverted, others not */
        {
          bad = 1;
          break;
        }
      }
    }
    else
    {
      if ( unitOne.unitNumerator[i] == -unitTwo.unitNumerator[i] )
      {
        /* this unit needs to be inverted */
        inv = 1;
      }
      else /* error: output units not equal to input or inverse of input */
      {
        bad = 1;
        break;
      }
    }
  }
  if ( bad ) /* units were bad: abort */
  {
    ABORT( status, CALIBRATIONH_EUNIT, CALIBRATIONH_MSGEUNIT );
  }

  /* determine if there is a scale factor that needs to be applied */
  fac = unitOne.powerOfTen - ( inv ? -unitTwo.powerOfTen : unitTwo.powerOfTen );

  /* perform conversion(s) */

  if ( inv ) /* invert data */
  {
    for ( i = 0; i < output->data->length; ++i )
    {
      output->data->data[i] = 1.0 / output->data->data[i];
    }
  }

  if ( fac ) /* scale data */
  {
    REAL4 scale = pow( 10.0, -fac );
    for ( i = 0; i < output->data->length; ++i )
    {
      output->data->data[i] *= scale;
    }
  }

  DETATCHSTATUSPTR( status );
  RETURN( status );
}