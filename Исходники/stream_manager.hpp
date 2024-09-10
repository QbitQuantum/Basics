  static inline int count_trailing_zeros(word_t word) {
#if defined(__GNUC__)
    return __builtin_ctzl(word);
#elif defined(_MSC_VER)
    unsigned long index;
#  if defined(_M_AMD64)
    assert(_BitScanForward64(&index, word) != 0);
#  else
    assert(_BitScanForward(&index, word) != 0);
#  endif
    return static_cast<int>(index);
#else
#endif
  }