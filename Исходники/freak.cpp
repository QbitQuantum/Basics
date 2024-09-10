void FREAK::extractDescriptor(uchar *pointsValue, void ** ptr) const
{
    __m128i** ptrSSE = (__m128i**) ptr;

    // note that comparisons order is modified in each block (but first 128 comparisons remain globally the same-->does not affect the 128,384 bits segmanted matching strategy)
    int cnt = 0;
    for( int n = FREAK_NB_PAIRS/128; n-- ; )
    {
        __m128i result128 = _mm_setzero_si128();
        for( int m = 128/16; m--; cnt += 16 )
        {
            __m128i operand1 = _mm_set_epi8(pointsValue[descriptionPairs[cnt+0].i],
                                            pointsValue[descriptionPairs[cnt+1].i],
                                            pointsValue[descriptionPairs[cnt+2].i],
                                            pointsValue[descriptionPairs[cnt+3].i],
                                            pointsValue[descriptionPairs[cnt+4].i],
                                            pointsValue[descriptionPairs[cnt+5].i],
                                            pointsValue[descriptionPairs[cnt+6].i],
                                            pointsValue[descriptionPairs[cnt+7].i],
                                            pointsValue[descriptionPairs[cnt+8].i],
                                            pointsValue[descriptionPairs[cnt+9].i],
                                            pointsValue[descriptionPairs[cnt+10].i],
                                            pointsValue[descriptionPairs[cnt+11].i],
                                            pointsValue[descriptionPairs[cnt+12].i],
                                            pointsValue[descriptionPairs[cnt+13].i],
                                            pointsValue[descriptionPairs[cnt+14].i],
                                            pointsValue[descriptionPairs[cnt+15].i]);

            __m128i operand2 = _mm_set_epi8(pointsValue[descriptionPairs[cnt+0].j],
                                            pointsValue[descriptionPairs[cnt+1].j],
                                            pointsValue[descriptionPairs[cnt+2].j],
                                            pointsValue[descriptionPairs[cnt+3].j],
                                            pointsValue[descriptionPairs[cnt+4].j],
                                            pointsValue[descriptionPairs[cnt+5].j],
                                            pointsValue[descriptionPairs[cnt+6].j],
                                            pointsValue[descriptionPairs[cnt+7].j],
                                            pointsValue[descriptionPairs[cnt+8].j],
                                            pointsValue[descriptionPairs[cnt+9].j],
                                            pointsValue[descriptionPairs[cnt+10].j],
                                            pointsValue[descriptionPairs[cnt+11].j],
                                            pointsValue[descriptionPairs[cnt+12].j],
                                            pointsValue[descriptionPairs[cnt+13].j],
                                            pointsValue[descriptionPairs[cnt+14].j],
                                            pointsValue[descriptionPairs[cnt+15].j]);

            __m128i workReg = _mm_min_epu8(operand1, operand2); // emulated "not less than" for 8-bit UNSIGNED integers
            workReg = _mm_cmpeq_epi8(workReg, operand2);        // emulated "not less than" for 8-bit UNSIGNED integers

            workReg = _mm_and_si128(_mm_set1_epi16(short(0x8080 >> m)), workReg); // merge the last 16 bits with the 128bits std::vector until full
            result128 = _mm_or_si128(result128, workReg);
        }
        (**ptrSSE) = result128;
        ++(*ptrSSE);
    }
    (*ptrSSE) -= 8;
}