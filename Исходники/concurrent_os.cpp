 int64_t Atomics::CompareAndSet64Val(int64_t* ptr, int64_t expVal, int64_t newVal)
 {
     return _InterlockedCompareExchange64(reinterpret_cast<LONG64*>(ptr), newVal, expVal);
 }