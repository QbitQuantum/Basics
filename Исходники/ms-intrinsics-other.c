LONG test_InterlockedExchangeAdd(LONG volatile *value, LONG mask) {
  return _InterlockedExchangeAdd(value, mask);
}