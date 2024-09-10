void AES_Key_Expansion_PARA_3(
        const unsigned char *userkey1,
        const unsigned char *userkey2,
        const unsigned char *userkey3,
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3)
{
    __m128i temp1_1, temp2_1;
    __m128i temp1_2, temp2_2, temp3_2, temp4_2; 
    __m128i temp1_3, temp2_3;

    __m128i *Key_Schedule1 = (__m128i*)key1; 
    __m128i *Key_Schedule2 = (__m128i*)key2; 
    __m128i *Key_Schedule3 = (__m128i*)key3; 
     
    temp1_1 = _mm_loadu_si128((__m128i*)userkey1); 
    temp1_2 = _mm_loadu_si128((__m128i*)userkey2); 
    temp3_2 = _mm_loadu_si128((__m128i*)(userkey2+16)); 
    temp1_3 = _mm_loadu_si128((__m128i*)userkey3); 
    Key_Schedule1[0] = temp1_1; 
    Key_Schedule2[0] = temp1_2; 
    Key_Schedule2[1] = temp3_2; 
    Key_Schedule3[0] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1 ,0x1); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2 ,0x1); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3 ,0x1); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[1] = temp1_1; 
    Key_Schedule2[1] = (__m128i)_mm_shuffle_pd((__m128d)Key_Schedule2[1], (__m128d)temp1_2,0); 
    Key_Schedule2[2] = (__m128i)_mm_shuffle_pd((__m128d)temp1_2, (__m128d)temp3_2,1); 
    Key_Schedule3[1] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x2); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x2);
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x2); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[2] = temp1_1;   
    Key_Schedule2[3] = temp1_2; 
    Key_Schedule2[4] = temp3_2; 
    Key_Schedule3[2] = temp1_3;   
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x4); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x4); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x4); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[3] = temp1_1; 
    Key_Schedule2[4] = (__m128i)_mm_shuffle_pd((__m128d)Key_Schedule2[4], (__m128d)temp1_2,0); 
    Key_Schedule2[5] = (__m128i)_mm_shuffle_pd((__m128d)temp1_2,(__m128d)temp3_2,1); 
    Key_Schedule3[3] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x8); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x8); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x8); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[4] = temp1_1; 
    Key_Schedule2[6] = temp1_2; 
    Key_Schedule2[7] = temp3_2; 
    Key_Schedule3[4] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x10); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x10); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x10); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[5] = temp1_1; 
    Key_Schedule2[7] = (__m128i)_mm_shuffle_pd((__m128d)Key_Schedule2[7], (__m128d)temp1_2,0); 
    Key_Schedule2[8] = (__m128i)_mm_shuffle_pd((__m128d)temp1_2,(__m128d)temp3_2,1); 
    Key_Schedule3[5] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x20); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x20); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x20); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[6] = temp1_1; 
    Key_Schedule2[9] = temp1_2; 
    Key_Schedule2[10]= temp3_2; 
    Key_Schedule3[6] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x40); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x40); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x40); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[7] = temp1_1; 
    Key_Schedule2[10]= (__m128i)_mm_shuffle_pd((__m128d)Key_Schedule2[10], (__m128d)temp1_2,0); 
    Key_Schedule2[11]= (__m128i)_mm_shuffle_pd((__m128d)temp1_2,(__m128d)temp3_2,1); 
    Key_Schedule3[7] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x80); 
    temp2_2 = _mm_aeskeygenassist_si128 (temp3_2,0x80); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x80); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    KEY_192_ASSIST(&temp1_2, &temp2_2, &temp3_2); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    /*KEY_ASSIST_PARA_3(
            temp1_1, temp2_1, &temp1_1,
            &temp1_2, &temp2_2, &temp3_2,
            temp1_3, temp2_3, &temp1_3);*/
    Key_Schedule1[8] = temp1_1;     
    Key_Schedule2[12]= temp1_2;    
    Key_Schedule3[8] = temp1_3;     
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x1b); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x1b); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    Key_Schedule1[9] = temp1_1; 
    Key_Schedule3[9] = temp1_3; 
    temp2_1 = _mm_aeskeygenassist_si128 (temp1_1,0x36); 
    temp2_3 = _mm_aeskeygenassist_si128 (temp1_3,0x36); 
    temp1_1 = AES_128_ASSIST(temp1_1, temp2_1); 
    temp1_3 = AES_128_ASSIST(temp1_3, temp2_3); 
    Key_Schedule1[10] = temp1_1; 
    Key_Schedule3[10] = temp1_3; 
}