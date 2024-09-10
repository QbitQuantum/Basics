/*
* AES-256 Key Schedule
*/
void AES_256_NI::key_schedule(const byte key[], size_t)
   {
   __m128i K0 = _mm_loadu_si128((const __m128i*)(key));
   __m128i K1 = _mm_loadu_si128((const __m128i*)(key + 16));

   __m128i K2 = aes_128_key_expansion(K0, _mm_aeskeygenassist_si128(K1, 0x01));
   __m128i K3 = aes_256_key_expansion(K1, K2);

   __m128i K4 = aes_128_key_expansion(K2, _mm_aeskeygenassist_si128(K3, 0x02));
   __m128i K5 = aes_256_key_expansion(K3, K4);

   __m128i K6 = aes_128_key_expansion(K4, _mm_aeskeygenassist_si128(K5, 0x04));
   __m128i K7 = aes_256_key_expansion(K5, K6);

   __m128i K8 = aes_128_key_expansion(K6, _mm_aeskeygenassist_si128(K7, 0x08));
   __m128i K9 = aes_256_key_expansion(K7, K8);

   __m128i K10 = aes_128_key_expansion(K8, _mm_aeskeygenassist_si128(K9, 0x10));
   __m128i K11 = aes_256_key_expansion(K9, K10);

   __m128i K12 = aes_128_key_expansion(K10, _mm_aeskeygenassist_si128(K11, 0x20));
   __m128i K13 = aes_256_key_expansion(K11, K12);

   __m128i K14 = aes_128_key_expansion(K12, _mm_aeskeygenassist_si128(K13, 0x40));

   __m128i* EK_mm = (__m128i*)&EK[0];
   _mm_storeu_si128(EK_mm     , K0);
   _mm_storeu_si128(EK_mm +  1, K1);
   _mm_storeu_si128(EK_mm +  2, K2);
   _mm_storeu_si128(EK_mm +  3, K3);
   _mm_storeu_si128(EK_mm +  4, K4);
   _mm_storeu_si128(EK_mm +  5, K5);
   _mm_storeu_si128(EK_mm +  6, K6);
   _mm_storeu_si128(EK_mm +  7, K7);
   _mm_storeu_si128(EK_mm +  8, K8);
   _mm_storeu_si128(EK_mm +  9, K9);
   _mm_storeu_si128(EK_mm + 10, K10);
   _mm_storeu_si128(EK_mm + 11, K11);
   _mm_storeu_si128(EK_mm + 12, K12);
   _mm_storeu_si128(EK_mm + 13, K13);
   _mm_storeu_si128(EK_mm + 14, K14);

   // Now generate decryption keys

   __m128i* DK_mm = (__m128i*)&DK[0];
   _mm_storeu_si128(DK_mm     , K14);
   _mm_storeu_si128(DK_mm +  1, _mm_aesimc_si128(K13));
   _mm_storeu_si128(DK_mm +  2, _mm_aesimc_si128(K12));
   _mm_storeu_si128(DK_mm +  3, _mm_aesimc_si128(K11));
   _mm_storeu_si128(DK_mm +  4, _mm_aesimc_si128(K10));
   _mm_storeu_si128(DK_mm +  5, _mm_aesimc_si128(K9));
   _mm_storeu_si128(DK_mm +  6, _mm_aesimc_si128(K8));
   _mm_storeu_si128(DK_mm +  7, _mm_aesimc_si128(K7));
   _mm_storeu_si128(DK_mm +  8, _mm_aesimc_si128(K6));
   _mm_storeu_si128(DK_mm +  9, _mm_aesimc_si128(K5));
   _mm_storeu_si128(DK_mm + 10, _mm_aesimc_si128(K4));
   _mm_storeu_si128(DK_mm + 11, _mm_aesimc_si128(K3));
   _mm_storeu_si128(DK_mm + 12, _mm_aesimc_si128(K2));
   _mm_storeu_si128(DK_mm + 13, _mm_aesimc_si128(K1));
   _mm_storeu_si128(DK_mm + 14, K0);
   }