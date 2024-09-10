ULONG MathFunc(CHAR *name, ULONG numargs, RXSTRING args[],
                        CHAR *queuename, RXSTRING *retstr)
{
	double x, y, result;
	int i, fn_id = -1;

#ifdef ENABLE_CACHE
   if (RxMathFncCache.id >= 0)
      fn_id = cache_func(name, numargs);

   if (fn_id < 0)
   {
   	fn_id = resolve_func(name, numargs);
	   if (fn_id < 0)           
		   return INVALID_ROUTINE;
   }
#else
  	fn_id = resolve_func(name, numargs);
   if (fn_id < 0)           
	   return INVALID_ROUTINE;
#endif

	x = atof(args[0].strptr);
	if (numargs > 1L)
	{
		y = atof(args[1].strptr);
		i = atoi(args[1].strptr);
	}

	switch (fn_id)
	{
	case fn_acos:
		result = acos(x);
		break;
	case fn_asin: 
		result = asin(x);
		break;
	case fn_atan: 
		result = atan(x);
		break;
	case fn_atan2:
		result = atan2(x, y);
		break;
	case fn_ceil: 
		result = ceil(x);
		break;
	case fn_cos:  
		result = cos(x);
		break;
	case fn_cosh: 
		result = cosh(x);
		break;
	case fn_exp:  
		result = exp(x);
		break;
	case fn_fabs: 
		result = fabs(x);
		break;
	case fn_floor:
		result = floor(x);
		break;
	case fn_fmod: 
		result = fmod(x, y);
		break;
	case fn_frexp:
		result = frexp(x, &i);
		break;
	case fn_ldexp:
		result = ldexp(x, i);
		break;
	case fn_log:  
		result = log(x);
		break;
	case fn_log10:
		result = log10(x);
		break;
	case fn_modf: 
		result = modf(x, &y);
		break;
	case fn_pow:  
		result = pow(x, y);
		break;
	case fn_sin:  
		result = sin(x);
		break;
	case fn_sinh: 
		result = sinh(x);
		break;
	case fn_sqrt: 
		result = sqrt(x);
		break;
	case fn_tan: 
		result = tan(x);
		break;
	case fn_tanh:
		result = tanh(x);
		break;
#ifdef __IBMC__
	case fn_erf:
      result = erf( x );
		break;
	case fn_erfc:  
      result = erfc( x );
		break;
	case fn_gamma: 
      result = gamma( x );
		break;
#endif
	case fn_hypot: 
      result = hypot( x, y );
		break;
	case fn_j0:    
      result = j0( x );
		break;
	case fn_j1:    
      result = j1( x );
		break;
	case fn_jn:    
      result = jn( i, x );
		break;
	case fn_y0:    
      result = y0( x );
		break;
	case fn_y1:    
      result = y1( x );
		break;
	case fn_yn:    
      result = yn( i, x );
		break;
	case fn_pi:    
      result = 3.1415926575;
		break;
   default:
	   return INVALID_ROUTINE;
	}

	switch (fn_id)
	{
	case fn_frexp:
		sprintf(retstr->strptr, "%lf %i", result, i);
		break;
	case fn_modf: 
		sprintf(retstr->strptr, "%lf %lf", result, y);
		break;
	default:
		sprintf(retstr->strptr, "%lf", result);
		break;
	}

	retstr->strlength = strlen(retstr->strptr);
	return VALID_ROUTINE;
}