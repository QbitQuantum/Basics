long test_InterlockedAdd(long volatile *Addend, long Value) {
  return _InterlockedAdd(Addend, Value);
}