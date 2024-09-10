void e() {
  d.m_fn2();
  try {
    a();
    _setjmp(0);
  } catch (...) {
  }
}