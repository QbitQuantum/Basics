int
ipmi_sensor_decode_tolerance (int8_t r_exponent,
                              int16_t m,
                              uint8_t linearization,
                              uint8_t raw_data,
                              double *value)
{
  double dval = 0.0;

  if (!value
      || !IPMI_SDR_LINEARIZATION_IS_LINEAR (linearization))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  /* note no analog_data format, tolerance always stored as unsigned */

  dval = (double) raw_data;

  dval *= (double) m;
  dval /= 2.0;
  dval += (dval * pow (10, r_exponent));

  switch (linearization)
    {
    case IPMI_SDR_LINEARIZATION_LN:
      dval = log (dval);
      break;
    case IPMI_SDR_LINEARIZATION_LOG10:
      dval = log10 (dval);
      break;
    case IPMI_SDR_LINEARIZATION_LOG2:
      dval = log2 (dval);
      break;
    case IPMI_SDR_LINEARIZATION_E:
      dval = exp (dval);
      break;
    case IPMI_SDR_LINEARIZATION_EXP10:
      dval = exp10 (dval);
      break;
    case IPMI_SDR_LINEARIZATION_EXP2:
      dval = exp2 (dval);
      break;
    case IPMI_SDR_LINEARIZATION_INVERSE:
      if (dval != 0.0)
	dval = 1.0 / dval;
      break;
    case IPMI_SDR_LINEARIZATION_SQR:
      dval = pow (dval, 2.0);
      break;
    case IPMI_SDR_LINEARIZATION_CUBE:
      dval = pow (dval, 3.0);
      break;
    case IPMI_SDR_LINEARIZATION_SQRT:
      dval = sqrt (dval);
      break;
    case IPMI_SDR_LINEARIZATION_CUBERT:
      dval = cbrt (dval);
      break;
    }

  *value = dval;
  return (0);
}