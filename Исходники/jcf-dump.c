static void
print_constant (FILE *out, JCF *jcf, int index, int verbosity)
{
  int j, n;
  jlong num;
  const char *str;
  int kind = JPOOL_TAG (jcf, index);
  switch (kind)
    {
    case CONSTANT_Class:
      n = JPOOL_USHORT1 (jcf, index);
      if (verbosity > 0)
	{
	  if (verbosity > 1)
	    fprintf (out, "Class name: %d=", n);
	  else
	    fprintf (out, "Class ");
	}
      if (! CPOOL_INDEX_IN_RANGE (&jcf->cpool, n))
	fprintf (out, "<out of range>");
      else if (verbosity < 2 && JPOOL_TAG (jcf, n) == CONSTANT_Utf8)
	{
	  int len = JPOOL_UTF_LENGTH (jcf, n);
	  jcf_print_utf8_replace (out, JPOOL_UTF_DATA(jcf,n), len, '/', '.');
	}
      else
	print_constant_terse (out, jcf, n, CONSTANT_Utf8);
      break;
    case CONSTANT_Fieldref:
      str = "Field"; goto field_or_method;
    case CONSTANT_Methodref:
      str = "Method"; goto field_or_method;
    case CONSTANT_InterfaceMethodref:
      str = "InterfaceMethod"; goto field_or_method;
    field_or_method:
      {
	uint16 tclass = JPOOL_USHORT1 (jcf, index);
	uint16 name_and_type = JPOOL_USHORT2 (jcf, index);
	if (verbosity == 2)
	  fprintf (out, "%sref class: %d=", str, tclass);
	else if (verbosity > 0)
	    fprintf (out, "%s ", str);
	print_constant_terse (out, jcf, tclass, CONSTANT_Class);
	if (verbosity < 2)
	  fprintf (out, ".");
	else
	  fprintf (out, " name_and_type: %d=<", name_and_type);
	print_constant_terse (out, jcf, name_and_type, CONSTANT_NameAndType);
	if (verbosity == 2)
	  fputc ('>', out);
      }
      break;
    case CONSTANT_String:
      j = JPOOL_USHORT1 (jcf, index);
      if (verbosity > 0)
	{
	  if (verbosity > 1)
	    fprintf (out, "String %d=", j);
	  else
	    fprintf (out, "String ");
	}
      print_constant_terse (out, jcf, j, CONSTANT_Utf8);
      break;
    case CONSTANT_Integer:
      if (verbosity > 0)
	fprintf (out, "Integer ");
      num = JPOOL_INT (jcf, index);
      goto integer;
    case CONSTANT_Long:
      if (verbosity > 0)
	fprintf (out, "Long ");
      num = JPOOL_LONG (jcf, index);
      goto integer;
    integer:
      {
	char buffer[25];
	format_int (buffer, num, 10);
	fprintf (out, "%s", buffer);
	if (verbosity > 1)
	  {
	    format_uint (buffer, (uint64)num, 16);
	    fprintf (out, "=0x%s", buffer);
	  }
      }
      break;
    case CONSTANT_Float:
      {
	jfloat fnum = JPOOL_FLOAT (jcf, index);

	if (verbosity > 0)
	  fputs ("Float ", out);

	if (fnum.negative)
	  putc ('-', out);

	if (JFLOAT_FINITE (fnum))
	  {
	    int dummy;
	    int exponent = fnum.exponent - JFLOAT_EXP_BIAS;
	    double f;
	    uint32 mantissa = fnum.mantissa;
	    if (fnum.exponent == 0)
	      /* Denormal.  */
	      exponent++;
	    else
	      /* Normal; add the implicit bit.  */
	      mantissa |= ((uint32)1 << 23);
	    
	    f = frexp (mantissa, &dummy);
	    f = ldexp (f, exponent + 1);
	    fprintf (out, "%.10g", f);
	  }
	else
	  {
	    if (fnum.mantissa == 0)
	      fputs ("Inf", out);
	    else if (fnum.mantissa & JFLOAT_QNAN_MASK)
	      fprintf (out, "QNaN(%u)", (fnum.mantissa & ~JFLOAT_QNAN_MASK));
	    else
	      fprintf (out, "SNaN(%u)", (fnum.mantissa & ~JFLOAT_QNAN_MASK));
	  }

	if (verbosity > 1)
	  fprintf (out, ", bits = 0x%08lx", JPOOL_UINT (jcf, index));
	
	break;
      }
    case CONSTANT_Double:
      {
	jdouble dnum = JPOOL_DOUBLE (jcf, index);

	if (verbosity > 0)
	  fputs ("Double ", out);

	if (dnum.negative)
	  putc ('-', out);

	if (JDOUBLE_FINITE (dnum))
	  {
	    int dummy;
	    int exponent = dnum.exponent - JDOUBLE_EXP_BIAS;
	    double d;
	    uint64 mantissa = ((((uint64) dnum.mantissa0) << 32)
			       + dnum.mantissa1);
	    if (dnum.exponent == 0)
	      /* Denormal.  */
	      exponent++;
	    else
	      /* Normal; add the implicit bit.  */
	      mantissa |= ((uint64)1 << 52);

	    d = frexp (mantissa, &dummy);
	    d = ldexp (d, exponent + 1);
	    fprintf (out, "%.20g", d);
	  }
	else
	  {
	    uint64 mantissa = dnum.mantissa0 & ~JDOUBLE_QNAN_MASK;
	    mantissa = (mantissa << 32) + dnum.mantissa1;

	    if (dnum.mantissa0 == 0 && dnum.mantissa1 == 0)
	      fputs ("Inf", out);
	    else if (dnum.mantissa0 & JDOUBLE_QNAN_MASK)
	      fprintf (out, "QNaN(%llu)", (unsigned long long)mantissa);
	    else
	      fprintf (out, "SNaN(%llu)", (unsigned long long)mantissa);
	  }
	if (verbosity > 1)
	  {
	    int32 hi, lo;
	    hi = JPOOL_UINT (jcf, index);
	    lo = JPOOL_UINT (jcf, index + 1);
	    fprintf (out, ", bits = 0x%08lx%08lx", (long) hi, (long) lo);
	  }
	break;
      }
    case CONSTANT_NameAndType:
      {
	uint16 name = JPOOL_USHORT1 (jcf, index);
	uint16 sig = JPOOL_USHORT2 (jcf, index);
	if (verbosity > 0)
	  {
	    if (verbosity > 1)
	      fprintf (out, "NameAndType name: %d=", name);
	    else
	      fprintf (out, "NameAndType ");
	  }
	print_name (out, jcf, name);
	if (verbosity <= 1)
	  fputc (' ', out);
	else
	  fprintf (out, ", signature: %d=", sig);
	print_signature (out, jcf, sig, 0);
      }
      break;
    case CONSTANT_Utf8:
      {
	const unsigned char *str = JPOOL_UTF_DATA (jcf, index);
	int length = JPOOL_UTF_LENGTH (jcf, index);
	if (verbosity > 0)
	  { /* Print as 8-bit bytes. */
	    fputs ("Utf8: \"", out);
	    while (--length >= 0)
	      jcf_print_char (out, *str++);
	  }
	else
	  { /* Print as Unicode. */
	    fputc ('\"', out);
	    jcf_print_utf8 (out, str, length);
	  }
	fputc ('\"', out);
      }
      break;
    default:
      fprintf (out, "(Unknown constant type %d)", kind);
    }
}