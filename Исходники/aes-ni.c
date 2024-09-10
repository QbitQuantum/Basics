void AESNI_Key_Expansion(const unsigned char *userkey, AES_KEY enc_key)
{
    __m128i temp1, temp2;
    __m128i *Key_Schedule = (__m128i*)enc_key;

    temp1 = _mm_loadu_si128((__m128i*)userkey);
    _mm_storeu_si128(&Key_Schedule[0], temp1);
    temp2= _mm_aeskeygenassist_si128 (temp1 ,0x1);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[1], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x2);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[2], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x4);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[3], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x8);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[4], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x10);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[5], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x20);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[6], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x40);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[7], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x80);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[8], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x1b);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[9], temp1);
    temp2 = _mm_aeskeygenassist_si128 (temp1,0x36);
    temp1 = AES_128_ASSIST(temp1, temp2);
    _mm_storeu_si128(&Key_Schedule[10], temp1);
}