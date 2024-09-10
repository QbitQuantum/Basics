// helper method for case where needles.size() <= 16
size_t qfind_first_byte_of_needles16(const StringPieceLite haystack,
                                     const StringPieceLite needles) {
  DCHECK_GT(haystack.size(), 0u);
  DCHECK_GT(needles.size(), 0u);
  DCHECK_LE(needles.size(), 16u);
  if ((needles.size() <= 2 && haystack.size() >= 256) ||
      // must bail if we can't even SSE-load a single segment of haystack
      (haystack.size() < 16 &&
       page_for(haystack.end() - 1) != page_for(haystack.data() + 15)) ||
      // can't load needles into SSE register if it could cross page boundary
      page_for(needles.end() - 1) != page_for(needles.data() + 15)) {
    return detail::qfind_first_byte_of_nosse(haystack, needles);
  }

  auto arr2 = _mm_loadu_si128(
      reinterpret_cast<const __m128i*>(needles.data()));
  // do an unaligned load for first block of haystack
  auto arr1 = _mm_loadu_si128(
      reinterpret_cast<const __m128i*>(haystack.data()));
  auto index =
      _mm_cmpestri(arr2, int(needles.size()), arr1, int(haystack.size()), 0);
  if (index < 16) {
    return index;
  }

  // Now, we can do aligned loads hereafter...
  size_t i = nextAlignedIndex(haystack.data());
  for (; i < haystack.size(); i+= 16) {
    arr1 =
        _mm_load_si128(reinterpret_cast<const __m128i*>(haystack.data() + i));
    index = _mm_cmpestri(
        arr2, int(needles.size()), arr1, int(haystack.size() - i), 0);
    if (index < 16) {
      return i + index;
    }
  }
  return std::string::npos;
}