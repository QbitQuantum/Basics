void c_opt_unrolled_8x(uint8_t *keys, uint8_t *data, uint8_t *dataOut) {

  __m128i mask        = _mm_set_epi8(0x0C, 0x03, 0x06, 0x09, 0x08, 0x0F, 0x02, 0x05,
                                     0x04, 0x0B, 0x0E, 0x01, 0x00, 0x07, 0x0A, 0x0D);

  __m128i mmrcon      = _mm_set_epi8(0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00,
                                     0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00);

  __m128i mmrconFinal = _mm_set_epi8(0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1b, 0x00,
                                     0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1b, 0x00);

  __m128i key  [8];
  __m128i rkey [8];
  __m128i state[8];
  __m128i tmp0;

  key[0]  = _mm_load_si128((__m128i*)&(keys[  0]));
  key[1]  = _mm_load_si128((__m128i*)&(keys[ 16]));
  key[2]  = _mm_load_si128((__m128i*)&(keys[ 32]));
  key[3]  = _mm_load_si128((__m128i*)&(keys[ 48]));
  key[4]  = _mm_load_si128((__m128i*)&(keys[ 64]));
  key[5]  = _mm_load_si128((__m128i*)&(keys[ 80]));
  key[6]  = _mm_load_si128((__m128i*)&(keys[ 96]));
  key[7]  = _mm_load_si128((__m128i*)&(keys[112]));

  transpose_state(rkey, key);
  transpose_state(&(rkey[4]), &(key[4]));

  state[0]  = _mm_load_si128((__m128i*)  data     );
  state[1]  = state[0];
  state[2]  = state[0];
  state[3]  = state[0];
  state[4]  = state[0];
  state[5]  = state[0];
  state[6]  = state[0];
  state[7]  = state[0];

  tmp0    = _mm_aesenclast_si128(rkey[3], mmrcon);
  tmp0    = _mm_shuffle_epi8(tmp0, mask);

  state[0]   = _mm_xor_si128(state[0], key[0]);
  state[1]   = _mm_xor_si128(state[1], key[1]);
  state[2]   = _mm_xor_si128(state[2], key[2]);
  state[3]   = _mm_xor_si128(state[3], key[3]);
  state[4]   = _mm_xor_si128(state[4], key[4]);
  state[5]   = _mm_xor_si128(state[5], key[5]);
  state[6]   = _mm_xor_si128(state[6], key[6]);
  state[7]   = _mm_xor_si128(state[7], key[7]);

  rkey[0]    = _mm_xor_si128(rkey[0], tmp0);

  tmp0    = _mm_aesenclast_si128(rkey[7], mmrcon);
  tmp0    = _mm_shuffle_epi8(tmp0, mask);
  mmrcon  = _mm_slli_epi16(mmrcon, 0x01);

  rkey[1]    = _mm_xor_si128(rkey[1], rkey[0]);
  rkey[2]    = _mm_xor_si128(rkey[2], rkey[1]);
  rkey[3]    = _mm_xor_si128(rkey[3], rkey[2]);

  rkey[4]    = _mm_xor_si128(rkey[4], tmp0);
  rkey[5]    = _mm_xor_si128(rkey[5], rkey[4]);
  rkey[6]    = _mm_xor_si128(rkey[6], rkey[5]);
  rkey[7]    = _mm_xor_si128(rkey[7], rkey[6]);

  _mm_prefetch((char const *)state, 0);

  transpose_state(key, rkey);
  transpose_state(&(key[4]), &(rkey[4]));

  for (uint8_t roundCounter = 1; roundCounter < 8; roundCounter++) {

    tmp0    = _mm_aesenclast_si128(rkey[3], mmrcon);
    tmp0    = _mm_shuffle_epi8(tmp0, mask);

    state[0]   = _mm_aesenc_si128(state[0], key[0]);
    state[1]   = _mm_aesenc_si128(state[1], key[1]);
    state[2]   = _mm_aesenc_si128(state[2], key[2]);
    state[3]   = _mm_aesenc_si128(state[3], key[3]);
    state[4]   = _mm_aesenc_si128(state[4], key[4]);
    state[5]   = _mm_aesenc_si128(state[5], key[5]);

    rkey[0]    = _mm_xor_si128(rkey[0], tmp0);
    tmp0    = _mm_aesenclast_si128(rkey[7], mmrcon);

    rkey[1]    = _mm_xor_si128(rkey[1], rkey[0]);
    rkey[2]    = _mm_xor_si128(rkey[2], rkey[1]);
    rkey[3]    = _mm_xor_si128(rkey[3], rkey[2]);

    state[6]   = _mm_aesenc_si128(state[6], key[6]);
    state[7]   = _mm_aesenc_si128(state[7], key[7]);

    transpose_state(key, rkey);

    tmp0    = _mm_shuffle_epi8(tmp0, mask);
    mmrcon  = _mm_slli_epi16(mmrcon, 0x01);

    rkey[4]    = _mm_xor_si128(rkey[4], tmp0);
    rkey[5]    = _mm_xor_si128(rkey[5], rkey[4]);
    rkey[6]    = _mm_xor_si128(rkey[6], rkey[5]);
    rkey[7]    = _mm_xor_si128(rkey[7], rkey[6]);

    _mm_prefetch((char const *)state, 0);
    transpose_state(&(key[4]), &(rkey[4]));

  }

  tmp0    = _mm_aesenclast_si128(rkey[3], mmrconFinal);
  tmp0    = _mm_shuffle_epi8(tmp0, mask);

  state[0]   = _mm_aesenc_si128(state[0], key[0]);
  state[1]   = _mm_aesenc_si128(state[1], key[1]);
  state[2]   = _mm_aesenc_si128(state[2], key[2]);
  state[3]   = _mm_aesenc_si128(state[3], key[3]);
  state[4]   = _mm_aesenc_si128(state[4], key[4]);
  state[5]   = _mm_aesenc_si128(state[5], key[5]);

  rkey[0]    = _mm_xor_si128(rkey[0], tmp0);
  tmp0       = _mm_aesenclast_si128(rkey[7], mmrconFinal);

  rkey[1]    = _mm_xor_si128(rkey[1], rkey[0]);
  rkey[2]    = _mm_xor_si128(rkey[2], rkey[1]);
  rkey[3]    = _mm_xor_si128(rkey[3], rkey[2]);

  state[6]   = _mm_aesenc_si128(state[6], key[6]);
  state[7]   = _mm_aesenc_si128(state[7], key[7]);

  transpose_state(key, rkey);

  tmp0          = _mm_shuffle_epi8(tmp0, mask);
  mmrconFinal   = _mm_slli_epi16(mmrconFinal, 0x01);

  rkey[4]    = _mm_xor_si128(rkey[4], tmp0);
  rkey[5]    = _mm_xor_si128(rkey[5], rkey[4]);
  rkey[6]    = _mm_xor_si128(rkey[6], rkey[5]);
  rkey[7]    = _mm_xor_si128(rkey[7], rkey[6]);

  _mm_prefetch((char const *)state, 0);
  transpose_state(&(key[4]), &(rkey[4]));

  tmp0    = _mm_aesenclast_si128(rkey[3], mmrconFinal);
  tmp0    = _mm_shuffle_epi8(tmp0, mask);

  state[0]   = _mm_aesenc_si128(state[0], key[0]);
  state[1]   = _mm_aesenc_si128(state[1], key[1]);
  state[2]   = _mm_aesenc_si128(state[2], key[2]);
  state[3]   = _mm_aesenc_si128(state[3], key[3]);
  state[4]   = _mm_aesenc_si128(state[4], key[4]);
  state[5]   = _mm_aesenc_si128(state[5], key[5]);

  rkey[0]    = _mm_xor_si128(rkey[0], tmp0);
  tmp0       = _mm_aesenclast_si128(rkey[7], mmrconFinal);

  rkey[1]    = _mm_xor_si128(rkey[1], rkey[0]);
  rkey[2]    = _mm_xor_si128(rkey[2], rkey[1]);
  rkey[3]    = _mm_xor_si128(rkey[3], rkey[2]);

  state[6]   = _mm_aesenc_si128(state[6], key[6]);
  state[7]   = _mm_aesenc_si128(state[7], key[7]);

  transpose_state(key, rkey);
  tmp0          = _mm_shuffle_epi8(tmp0, mask);

  state[0]   = _mm_aesenclast_si128(state[0], key[0]);
  state[1]   = _mm_aesenclast_si128(state[1], key[1]);
  state[2]   = _mm_aesenclast_si128(state[2], key[2]);
  state[3]   = _mm_aesenclast_si128(state[3], key[3]);

  rkey[4]    = _mm_xor_si128(rkey[4], tmp0);
  rkey[5]    = _mm_xor_si128(rkey[5], rkey[4]);
  rkey[6]    = _mm_xor_si128(rkey[6], rkey[5]);
  rkey[7]    = _mm_xor_si128(rkey[7], rkey[6]);

  transpose_state(&(key[4]), &(rkey[4]));

  state[4]   = _mm_aesenclast_si128(state[4], key[4]);
  state[5]   = _mm_aesenclast_si128(state[5], key[5]);
  state[6]   = _mm_aesenclast_si128(state[6], key[6]);
  state[7]   = _mm_aesenclast_si128(state[7], key[7]);

  _mm_store_si128((__m128i*)&(dataOut[  0]),  state[0]);
  _mm_store_si128((__m128i*)&(dataOut[ 16]),  state[1]);
  _mm_store_si128((__m128i*)&(dataOut[ 32]),  state[2]);
  _mm_store_si128((__m128i*)&(dataOut[ 48]),  state[3]);
  _mm_store_si128((__m128i*)&(dataOut[ 64]),  state[4]);
  _mm_store_si128((__m128i*)&(dataOut[ 80]),  state[5]);
  _mm_store_si128((__m128i*)&(dataOut[ 96]),  state[6]);
  _mm_store_si128((__m128i*)&(dataOut[112]),  state[7]);

}