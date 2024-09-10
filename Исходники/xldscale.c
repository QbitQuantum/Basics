_STD_BEGIN

#if !_DLONG
_CRTIMP2 short _LDscale(long double *px, long lexp)
{   /* scale *px by 2^lexp with checking */
    return (_Dscale((double *)px, lexp));
}