static void xgetbv(unsigned int op, unsigned int* eax, unsigned int* edx) {
  *eax = 0; *edx = 0;
  if (op == 0)
      *eax = _xgetbv(_XCR_XFEATURE_ENABLED_MASK);
}