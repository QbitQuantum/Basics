void __fastcall aes_AES128_expand_key_(
    AES_AES_Block key,
    AES_AES128_RoundKeys* encryption_keys)
{
    AES_Block128 prev = encryption_keys->keys[0] = key;
    prev = encryption_keys->keys[1] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x01));
    prev = encryption_keys->keys[2] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x02));
    prev = encryption_keys->keys[3] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x04));
    prev = encryption_keys->keys[4] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x08));
    prev = encryption_keys->keys[5] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x10));
    prev = encryption_keys->keys[6] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x20));
    prev = encryption_keys->keys[7] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x40));
    prev = encryption_keys->keys[8] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x80));
    prev = encryption_keys->keys[9] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x1b));
    prev = encryption_keys->keys[10] = aes_aes128_expand_key_assist(prev, _mm_aeskeygenassist_si128(prev, 0x36));
}