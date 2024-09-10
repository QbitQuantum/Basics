unsigned
Atomic::XOR(unsigned value)
{
#if defined(_OPENTHREADS_ATOMIC_USE_GCC_BUILTINS)
    return __sync_fetch_and_xor(&_value, value);
#elif defined(_OPENTHREADS_ATOMIC_USE_WIN32_INTERLOCKED)
    return _InterlockedXor(&_value, value);
#elif defined(_OPENTHREADS_ATOMIC_USE_BSD_ATOMIC)
    return OSAtomicXor32((uint32_t)value, (uint32_t *)&_value);
#else
# error This implementation should happen inline in the include file
#endif
}