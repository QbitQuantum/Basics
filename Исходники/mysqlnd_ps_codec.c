/* {{{ ps_fetch_float */
static void
ps_fetch_float(zval * zv, const MYSQLND_FIELD * const field, unsigned int pack_len, zend_uchar ** row)
{
	float fval;
	double dval;
	DBG_ENTER("ps_fetch_float");
	float4get(fval, *row);
	(*row)+= 4;
	DBG_INF_FMT("value=%f", fval);

	/*
	 * The following is needed to correctly support 4-byte floats.
	 * Otherwise, a value of 9.99 in a FLOAT column comes out of mysqli
	 * as 9.9998998641968.
	 *
	 * For GCC, we use the built-in decimal support to "up-convert" a
	 * 4-byte float to a 8-byte double.
	 * When that is not available, we fall back to converting the float
	 * to a string and then converting the string to a double. This mimics
	 * what MySQL does.
	 */
#ifdef HAVE_DECIMAL_FP_SUPPORT
	{
		typedef float dec32 __attribute__((mode(SD)));
		dec32 d32val = fval;

		/* The following cast is guaranteed to do the right thing */
		dval = (double) d32val;
	}
#elif defined(PHP_WIN32)
	{
		/* float datatype on Winows is already 4 byte but has a precision of 7 digits */
		char num_buf[2048];
		(void)_gcvt_s(num_buf, 2048, fval, field->decimals >= 31 ? 7 : field->decimals);
		dval = zend_strtod(num_buf, NULL);
	}
#else
	{
		char num_buf[2048]; /* Over allocated */
		char *s;

#ifndef FLT_DIG
# define FLT_DIG 6
#endif
		/* Convert to string. Ignoring localization, etc.
		 * Following MySQL's rules. If precision is undefined (NOT_FIXED_DEC i.e. 31)
		 * or larger than 31, the value is limited to 6 (FLT_DIG).
		 */
		s = php_gcvt(fval,
			     field->decimals >= 31 ? FLT_DIG : field->decimals,
			     '.',
			     'e',
			     num_buf);

		/* And now convert back to double */
		dval = zend_strtod(s, NULL);
	}
#endif

	ZVAL_DOUBLE(zv, dval);
	DBG_VOID_RETURN;
}