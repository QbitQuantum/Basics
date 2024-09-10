__m128i aes_schedule_round(__m128i* rcon, __m128i input1, __m128i input2)
   {
   if(rcon)
      {
      input2 = _mm_xor_si128(_mm_alignr_epi8(_mm_setzero_si128(), *rcon, 15),
                             input2);

      *rcon = _mm_alignr_epi8(*rcon, *rcon, 15); // next rcon

      input1 = _mm_shuffle_epi32(input1, 0xFF); // rotate
      input1 = _mm_alignr_epi8(input1, input1, 1);
      }

   __m128i smeared = _mm_xor_si128(input2, _mm_slli_si128(input2, 4));
   smeared = mm_xor3(smeared, _mm_slli_si128(smeared, 8), _mm_set1_epi8(0x5B));

   __m128i t = _mm_srli_epi32(_mm_andnot_si128(low_nibs, input1), 4);

   input1 = _mm_and_si128(low_nibs, input1);

   __m128i t2 = _mm_shuffle_epi8(k_inv2, input1);

   input1 = _mm_xor_si128(input1, t);

   __m128i t3 = _mm_xor_si128(t2, _mm_shuffle_epi8(k_inv1, t));
   __m128i t4 = _mm_xor_si128(t2, _mm_shuffle_epi8(k_inv1, input1));

   __m128i t5 = _mm_xor_si128(input1, _mm_shuffle_epi8(k_inv1, t3));
   __m128i t6 = _mm_xor_si128(t, _mm_shuffle_epi8(k_inv1, t4));

   return mm_xor3(_mm_shuffle_epi8(sb1u, t5),
                  _mm_shuffle_epi8(sb1t, t6),
                  smeared);
   }