_f_int4 _FP_CLASS_I4_R(_f_real8 x)
{
#if defined(__mips) || (defined(_LITTLE_ENDIAN) && defined(__sv2))

  int x_result;
  x_result = fp_class_d(x);

  switch(x_result) {
  case FP_NEG_ZERO: {
    return (FOR_K_FP_NEG_ZERO);
    break;
  }
  case FP_POS_ZERO: {
    return (FOR_K_FP_POS_ZERO);
    break;
  }
  case FP_NEG_DENORM: {
    return (FOR_K_FP_NEG_DENORM);
    break;
  }
  case FP_POS_DENORM: {
    return (FOR_K_FP_POS_DENORM);
    break;
  }
  case FP_NEG_INF: {
    return (FOR_K_FP_NEG_INF);
    break;
  }
  case FP_SNAN: {
    return (FOR_K_FP_SNAN);
    break;
  }
  case FP_QNAN: {
    return (FOR_K_FP_QNAN);
    break;
  }
  case FP_POS_INF: {
    return (FOR_K_FP_POS_INF);
    break;
  }
  case FP_NEG_NORM: {
    return (FOR_K_FP_NEG_NORM);
    break;
  }
  case FP_POS_NORM: {
    return (FOR_K_FP_POS_NORM);
    break;
  }
  default: {
    return -1;
    break;
  }
  } /* Switch(x_result) */

#elif (defined(_CRAYIEEE) && !defined(__mips)) || defined(_SOLARIS)

  /* if we must call fpclassify */
  int x_result;
  union _uval_r x_val;

  x_result = fpclassify(x);
  x_val.dwd = x;

  switch(x_result) {
  case FP_ZERO: {
    /* Test for pos/neg */
    if(x_val.parts.sign) {
      return (FOR_K_FP_NEG_ZERO);
    } else {
      return (FOR_K_FP_POS_ZERO);
    }
    break;
  }
  case FP_SUBNORMAL: {
    /* Test for pos/neg */
    if(x_val.parts.sign) {
      return (FOR_K_FP_NEG_DENORM);
    } else {
      return (FOR_K_FP_POS_DENORM);
    }
    break;
  }
  case FP_INFINITE: {
    /* Test for pos/neg */
    if(x_val.parts.sign) {
      return (FOR_K_FP_NEG_INF);
    } else {
      return (FOR_K_FP_POS_INF);
    }
    break;
  }
  case FP_NAN: {
    
#ifdef _CRAYT3E /* on the t3e, all NaNs are signal NaNs */
    return (FOR_K_FP_SNAN);
#else
    /* test for quiet/signal on others */
    if(x_val.parts.q_bit) {
      return (FOR_K_FP_QNAN);
    } else {
      return (FOR_K_FP_SNAN);
    }
#endif /* #ifdef _CRAYT3E */

    break;
  }
  case FP_NORMAL: {
    /* Test for pos/neg */
    if(x_val.parts.sign) {
      return (FOR_K_FP_NEG_NORM);
    } else {
      return (FOR_K_FP_POS_NORM);
    }
    break;
  }
  default: {
    return -1;
    break;
  }
  } /* End switch(x_result); */

#elif defined(_LITTLE_ENDIAN) && !defined(__sv2)

  union _uval_r x_val;

  x_val.dwd = x;
  if(x_val.parts.exp == 0)
    {
      if(x_val.parts.up == 0 &&
	 x_val.parts.lo == 0 &&
	 x_val.parts.q_bit == 0)
	{
	  if(x_val.parts.sign)
	    return (FOR_K_FP_NEG_ZERO);
	  else
	    return (FOR_K_FP_POS_ZERO);
	}
      else
	{
	  if(x_val.parts.sign)
	    return (FOR_K_FP_NEG_DENORM);
	  else
	    return (FOR_K_FP_POS_DENORM);
	}
    }
  else if(x_val.parts.exp == IEEE_64_EXPO_MAX)
    {
      if(x_val.parts.up == 0 &&
	 x_val.parts.lo == 0 &&
	 x_val.parts.q_bit == 0)
	{
	  if(x_val.parts.sign)
	    return (FOR_K_FP_NEG_INF);
	  else
	    return (FOR_K_FP_POS_INF);
	}
      else
	{
	  if(x_val.parts.q_bit)
	    return (FOR_K_FP_QNAN);
	  else
	    return (FOR_K_FP_SNAN);
	}
    }
  else if(x_val.parts.sign)
    return (FOR_K_FP_NEG_NORM);
  else
    return (FOR_K_FP_POS_NORM);

#endif /* #if defined(__mips) ... #elif defined(_CRAYT3E) && defined(__mips) */
  
  return -1;

}