void key_schedule(const unsigned char *k, u256 rk[40][16]) {
  int i, j;
  u256 tk1[32], tmp[32];

  unsigned char *tmp_key = malloc(32);

  for(i = 0; i < 2; i++)
    memcpy(tmp_key + 16*i, k, 16);
  pack_key(tk1, tmp_key);

  for(j = 0; j < 40; j++) {
    //Extract round key
    for(i = 0; i < 16; i++){
      rk[j][i] = tk1[i];
    }

    //Add constant into key
    u256 rc = _mm256_set_epi64x(0x000000FF000000FFull,
                                0x000000FF000000FFull,
                                0x000000FF000000FFull,
                                0x000000FF000000FFull);

    if(RC[j]>>5 & 1)
      rk[j][14] = XOR(rk[j][14], rc);
    if(RC[j]>>4 & 1)
      rk[j][15] = XOR(rk[j][15], rc);
    if(RC[j]>>3 & 1)
      rk[j][4] = XOR(rk[j][4], rc);
    if(RC[j]>>2 & 1)
      rk[j][5] = XOR(rk[j][5], rc);
    if(RC[j]>>1 & 1)
      rk[j][6] = XOR(rk[j][6], rc);
    if(RC[j]>>0 & 1)
      rk[j][7] = XOR(rk[j][7], rc);

    //Update TK1
    for(i = 0; i < 16; i++){
      tmp[16 + i] = tk1[0 + i];
    }

    //Apply bit permutation
    for(i = 0; i < 8; i++){
      tmp[0 + i] = XOR(_mm256_shuffle_epi8(tk1[16  + i], _mm256_set_epi8(0xff,28,0xff,29,0xff,24,0xff,25,0xff,20,0xff,21,0xff,16,0xff,17,0xff,12,0xff,13,0xff,8,0xff,9,0xff,4,0xff,5,0xff,0,0xff,1)),
                       _mm256_shuffle_epi8(tk1[24  + i], _mm256_set_epi8(29,0xff,31,0xff,25,0xff,27,0xff,21,0xff,23,0xff,17,0xff,19,0xff,13,0xff,15,0xff,9,0xff,11,0xff,5,0xff,7,0xff,1,0xff,3,0xff)));
      tmp[8 + i] = XOR(_mm256_shuffle_epi8(tk1[16  + i], _mm256_set_epi8(31,0xff,0xff,30,27,0xff,0xff,26,23,0xff,0xff,22,19,0xff,0xff,18,15,0xff,0xff,14,11,0xff,0xff,10,7,0xff,0xff,6,3,0xff,0xff,2)),
                       _mm256_shuffle_epi8(tk1[24  + i], _mm256_set_epi8(0xff,28,30,0xff,0xff,24,26,0xff,0xff,20,22,0xff,0xff,16,18,0xff,0xff,12,14,0xff,0xff,8,10,0xff,0xff,4,6,0xff,0xff,0,2,0xff)));
    }

    for(i = 0; i < 32; i++){
      tk1[i] = tmp[i];
    }
  }
  free(tmp_key);
}