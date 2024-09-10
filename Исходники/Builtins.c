static CYTHON_INLINE unsigned PY_LONG_LONG __Pyx_abs_longlong(PY_LONG_LONG x) {
    if (unlikely(x == -PY_LLONG_MAX-1))
        return ((unsigned PY_LONG_LONG)PY_LLONG_MAX) + 1U;
#if defined (__cplusplus) && __cplusplus >= 201103L
    return (unsigned PY_LONG_LONG) std::abs(x);
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    return (unsigned PY_LONG_LONG) llabs(x);
#elif defined (_MSC_VER) && defined (_M_X64)
    // abs() is defined for long, but 64-bits type on MSVC is long long.
    // Use MS-specific _abs64 instead.
    return (unsigned PY_LONG_LONG) _abs64(x);
#elif defined (__GNUC__)
    // gcc or clang on 64 bit windows.
    return (unsigned PY_LONG_LONG) __builtin_llabs(x);
#else
    if (sizeof(PY_LONG_LONG) <= sizeof(Py_ssize_t))
        return __Pyx_sst_abs(x);
    return (x<0) ? (unsigned PY_LONG_LONG)-x : (unsigned PY_LONG_LONG)x;
#endif
}