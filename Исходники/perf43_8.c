/*
 * Simulates an implementation of a
 * Littlun-like cipher many times, for speed
 * evaluation
 */
__m128i dummy_cipher_eval()
{
  __m128i x, k;
  unsigned long long tick1, tick2, dum;

  x = _mm_set_epi64x(0x0001020304050607, 0x08090a0b0c0d0e0f);
  k = _mm_set_epi64x(0x0a030d0c0f050607, 0x08090a000c0d0e0f);

  dum = 0;

  for (tick1 = 0; tick1 < 1ull << 31; tick1++)
    dum += 2*tick1 & (~tick1 | (tick1 >> 2));
  
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);
  x = SB(x);
  x = M128(x);

  tick1 = rdtsc();

//  // r1
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r2
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r3
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r4
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r5
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r6
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r7
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // r8
//  x = _mm_xor_si128(x,k);
//  x = SB(x);
//  x = M128(x);
//  // final
//  x = _mm_xor_si128(x,k);

  tick2 = rdtsc();

  printf("%llu ~ %llu cycles\n\n", dum, tick2 - tick1); 

  return x;
}