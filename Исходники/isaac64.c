/*Returns a uniform random float.
  The expected value is within FLT_MIN (e.g., 1E-37) of 0.5.
  _bits: An initial set of random bits.
  _base: This should be -(the number of bits in _bits), up to -64.
  Return: A float uniformly distributed between 0 (inclusive) and 1
           (exclusive).
          The average value was measured over 2**32 samples to be
           0.499991407275206357.*/
static float isaac64_float_bits(isaac64_ctx *_ctx,uint64_t _bits,int _base){
  float ret;
  int   nbits_needed;
  while(!_bits){
    if(_base+FLT_MANT_DIG<FLT_MIN_EXP)return 0;
    _base-=64;
    _bits=isaac64_next_uint64(_ctx);
  }
  nbits_needed=FLT_MANT_DIG-ilog_64_nz(_bits);
#if FLT_MANT_DIG>64
  ret=ldexpf((float)_bits,_base);
# if FLT_MANT_DIG>129
  while(64-nbits_needed<0){
# else
  if(64-nbits_needed<0){
# endif
    _base-=64;
    nbits_needed-=64;
    ret+=ldexpf((float)isaac64_next_uint64(_ctx),_base);
  }
  _bits=isaac64_next_uint64(_ctx)>>(64-nbits_needed);
  ret+=ldexpf((float)_bits,_base-nbits_needed);
#else
  if(nbits_needed>0){
    _bits=_bits<<nbits_needed|isaac64_next_uint64(_ctx)>>(64-nbits_needed);
  }
# if FLT_MANT_DIG<64
  else _bits>>=-nbits_needed;