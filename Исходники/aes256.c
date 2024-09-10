void __fastcall aes_AES256_expand_key_(
    AES_AES_Block key_lo,
    AES_AES_Block key_hi,
    AES_AES256_RoundKeys* encryption_keys)
{
    AES_AES_Block prev_lo, prev_hi;
    AES_AES_Block hwgen;

    prev_lo = encryption_keys->keys[0] = key_lo;
    prev_hi = encryption_keys->keys[1] = key_hi;

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x01);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[2] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0);
    hwgen = _mm_shuffle_epi32(hwgen, 0xaa);
    encryption_keys->keys[3] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x02);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[4] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0);
    hwgen = _mm_shuffle_epi32(hwgen, 0xaa);
    encryption_keys->keys[5] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x04);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[6] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0);
    hwgen = _mm_shuffle_epi32(hwgen, 0xaa);
    encryption_keys->keys[7] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x08);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[8] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0);
    hwgen = _mm_shuffle_epi32(hwgen, 0xaa);
    encryption_keys->keys[9] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x10);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[10] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0);
    hwgen = _mm_shuffle_epi32(hwgen, 0xaa);
    encryption_keys->keys[11] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x20);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[12] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0);
    hwgen = _mm_shuffle_epi32(hwgen, 0xaa);
    encryption_keys->keys[13] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);

    hwgen = _mm_aeskeygenassist_si128(prev_hi, 0x40);
    hwgen = _mm_shuffle_epi32(hwgen, 0xff);
    encryption_keys->keys[14] = aes_aes256_expand_key_assist(&prev_lo, &prev_hi, hwgen);
}