void
test_prefetch (char *p)
{
  _mm_prefetch (p, _MM_HINT_T0);
  _mm_prefetch (p+4, _MM_HINT_T1);
  _mm_prefetch (p+8, _MM_HINT_T2);
  _mm_prefetch (p+12, _MM_HINT_NTA);
}