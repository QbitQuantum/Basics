/*
  xor #
*/
static Term
p_xor(Term t1, Term t2 USES_REGS)
{
  switch (ETypeOfTerm(t1)) {
  case long_int_e:
    
    switch (ETypeOfTerm(t2)) {
    case long_int_e:
      /* two integers */
      RINT(IntegerOfTerm(t1) ^ IntegerOfTerm(t2));
    case double_e:
      return Yap_ArithError(TYPE_ERROR_INTEGER, t2, "#/2");
    case big_int_e:
#ifdef USE_GMP
      return Yap_gmp_xor_int_big(IntegerOfTerm(t1), t2);
#endif
    default:
      RERROR();
    }
    break;
  case double_e:
    return Yap_ArithError(TYPE_ERROR_INTEGER, t1, "#/2");
  case big_int_e:
#ifdef USE_GMP
    switch (ETypeOfTerm(t2)) {
    case long_int_e:
      return Yap_gmp_xor_int_big(IntegerOfTerm(t2), t1);
    case big_int_e:
      return Yap_gmp_xor_big_big(t1, t2);
    case double_e:
      return Yap_ArithError(TYPE_ERROR_INTEGER, t2, "#/2");
    default:
      RERROR();
    }
#endif
  default:
    RERROR();
  }
  RERROR();
}