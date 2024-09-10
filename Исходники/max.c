static uint32_t avx512maxbitas32int(const __m512i accumulator) {
  uint32_t ans1 = maxbitas32int(_mm512_castsi512_si256(accumulator));
  uint32_t ans2 = maxbitas32int(_mm512_extracti64x4_epi64(accumulator, 1));
  printf("ans1 = %u ans2 = % u\n", ans1, ans2);
  uint32_t ans = ans1 > ans2 ? ans1 : ans2;
  return bits(ans);
}