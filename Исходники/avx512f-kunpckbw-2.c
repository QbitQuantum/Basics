unpack (__mmask16 arg1, __mmask16 arg2)
{
  __mmask16 res;

  res = _mm512_kunpackb (arg1, arg2);

  return res;
}