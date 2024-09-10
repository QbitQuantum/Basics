void calin::math::hex_array::test_avx2_positive_hexid_to_ringid_segid_runid(unsigned hexid,
  unsigned& ringid, unsigned& segid, unsigned& runid)
{
#if defined(__AVX2__) and defined(__FMA__)
  __m256i vhexid = _mm256_set1_epi32(hexid);
  __m256i vringid;
  __m256i vsegid;
  __m256i vrunid;
  avx2_positive_hexid_to_ringid_segid_runid(vhexid, vringid, vsegid, vrunid);
  ringid = vringid[0];
  segid = vsegid[0];
  runid = vrunid[0];
#else
  throw std::runtime_error("AVX2 and FMA not available at compile time");
#endif
}