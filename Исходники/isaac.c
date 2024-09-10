/*Returns a uniform random float.
  The expected value is within FLT_MIN (e.g., 1E-37) of 0.5.
  _bits: An initial set of random bits.
  _base: This should be -(the number of bits in _bits), up to -32.
  Return: A float uniformly distributed between 0 (inclusive) and 1
           (exclusive).
          The average value was measured over 2**32 samples to be
           0.50000037448772916.*/
static float isaac_float_bits(isaac_ctx *_ctx,uint32_t _bits,int _base){
  float ret;
  int   nbits_needed;
  while(!_bits){
    if(_base+FLT_MANT_DIG<FLT_MIN_EXP)return 0;
    _base-=32;
    _bits=isaac_next_uint32(_ctx);
  }
  /*Note: This could also be determined with frexp(), for a slightly more
     portable solution, but that takes twice as long, and one has to worry
     about rounding effects, which can over-estimate the exponent when given
     FLT_MANT_DIG+1 consecutive one bits.
    Even the fallback C implementation of ILOGNZ_32() yields an implementation
     25% faster than the frexp() method.*/
  nbits_needed=FLT_MANT_DIG-ilog32_nz(_bits);
#if FLT_MANT_DIG>32
  ret=ldexpf((float)_bits,_base);
# if FLT_MANT_DIG>65
  while(32-nbits_needed<0){
# else
  if(32-nbits_needed<0){
# endif
    _base-=32;
    nbits_needed-=32;
    ret+=ldexpf((float)isaac_next_uint32(_ctx),_base);
  }
  _bits=isaac_next_uint32(_ctx)>>32-nbits_needed;
  ret+=ldexpf((float)_bits,_base-nbits_needed);
#else
  if(nbits_needed>0){
    _bits=_bits<<nbits_needed|isaac_next_uint32(_ctx)>>(32-nbits_needed);
  }
# if FLT_MANT_DIG<32
  else _bits>>=-nbits_needed;