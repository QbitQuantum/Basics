// Main spin update routine
__forceinline
void spinFlipCore(uint32_t* updated, const uint32_t* neighbours, const uint32_t* field,
                  unsigned int x, unsigned int y, unsigned int z, __m512i rndInt)
{
#ifdef __MIC__
  const __m512i one = _mm512_set1_epi32(0xFFFFFFFF);
  const __m512i zero = _mm512_setzero_epi32();

  // calculate indices
  unsigned int x0 = (x+N-1)%N;
  unsigned int y0 = (y+N-1)%N;
  unsigned int z0 = (z+N-1)%N;
  unsigned int x1 = (x+17)%N;
  unsigned int y1 = (y+1)%N;
  unsigned int z1 = (z+1)%N;

  // neighbour spins
  Iu32vec16 n[6];
  n[0] = _mm512_loadunpacklo_epi32(_mm512_undefined_epi32(), neighbours + z*N*N + y*N + x0);
  n[0] = _mm512_loadunpackhi_epi32(n[0], neighbours + z*N*N + y*N + x + 16 - 1);
  n[1] = _mm512_loadunpacklo_epi32(_mm512_undefined_epi32(), neighbours + z*N*N + y*N + x + 1);
  n[1] = _mm512_loadunpackhi_epi32(n[1], neighbours + z*N*N + y*N + x1);
  n[2] = _mm512_load_epi32(neighbours + z*N*N + y0*N + x);
  n[3] = _mm512_load_epi32(neighbours + z*N*N + y1*N + x);
  n[4] = _mm512_load_epi32(neighbours + z0*N*N + y*N + x);
  n[5] = _mm512_load_epi32(neighbours + z1*N*N + y*N + x);
  
  // bits are set if spins are antiparallel
  unsigned int i = z*N*N + y*N + x;
  Iu32vec16 current = _mm512_load_epi32(updated + i);
  #pragma unroll(6)
  for(int j = 0; j < 6; ++j)
    n[j] = current ^ n[j];

  // count wrong spins using vertical counters
  Iu32vec16 c0, c1, c2, carry;

  c0 = n[0] ^ n[1];
  c1 = n[0] & n[1];
  
  c0 ^= n[2];
  c1 |= andn(c0, n[2]);
  
  c0 ^= n[3];
  carry = andn(c0, n[3]);
  c1 ^= carry;
  c2 = andn(c1, carry);
  
  c0 ^= n[4];
  carry = andn(c0, n[4]);
  c1 ^= carry;
  c2 |= andn(c1, carry);

  c0 ^= n[5];
  carry = andn(c0, n[5]);
  c1 ^= carry;
  c2 |= andn(c1, carry);
  
  Iu32vec16 w1 = andn(c2, andn(c1, c0));
  Iu32vec16 w2 = andn(c2, andn(c0, c1));
  Iu32vec16 w3 = andn(c2, c0 & c1);
  Iu32vec16 w4 = andn(c0, andn(c1, c2));
  Iu32vec16 w5 = andn(c1, c0 & c2);
  Iu32vec16 w6 = andn(c0, c1 & c2);
  
  // relation to field
  Iu32vec16 e[7];
  Iu32vec16 f = current ^ _mm512_load_epi32(field + i);
  #pragma unroll(7)
  for(int j = 0; j < 7; j++)
  {
    __mmask16 ep = _mm512_cmple_epu32_mask(rndInt, _mm512_set1_epi32(expBeta[2*j]));
    __mmask16 em = _mm512_cmple_epu32_mask(rndInt, _mm512_set1_epi32(expBeta[2*j+1]));
    e[6-j] = _mm512_mask_mov_epi32(_mm512_mask_mov_epi32(zero, em, f), ep, one);
  }

  // check for spin flip
  Iu32vec16 flip = e[0] | e[1] & w1 | e[2] & w2 | e[3] & w3 | e[4] & w4 | e[5] & w5 | e[6] & w6;
  _mm512_store_epi32(updated + i, flip ^ current);
#endif
}