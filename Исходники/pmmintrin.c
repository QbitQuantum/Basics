int __attribute__((__target__(("sse3")))) foo(int a) {
  _mm_mwait(0, 0);
  return 4;
}