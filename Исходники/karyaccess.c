static inline bool avxcontains(hashset_t * set, uint64_t target) {
  __m256i vtarget = _mm256_set1_epi64x(target);
  __m256i vlocation = _mm256_and_si256(avxhash(vtarget, set->vmultiplier),set->sizemask);
  __m256i svalue = _mm256_i64gather_epi64((const long long int *) set->data,vlocation,8);
  __m256i eq = _mm256_cmpeq_epi64(vtarget,svalue);
  return _mm256_testz_si256(eq,eq) == 0;
}