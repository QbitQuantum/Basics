unpack (__mmask64 arg1, __mmask64 arg2)
{
  __mmask64 res;

  res = _mm512_kunpackd (arg1, arg2);

  return res;
}