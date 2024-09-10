unpack (__mmask32 arg1, __mmask32 arg2)
{
  __mmask32 res;

  res = _mm512_kunpackw (arg1, arg2);

  return res;
}