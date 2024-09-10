void Convert444to420(LPBYTE input, int width, int pitch, int height, int startY, int endY, LPBYTE *output, bool bSSE2Available)
{
    LPBYTE lumPlane     = output[0];
    LPBYTE uPlane       = output[1];
    LPBYTE vPlane       = output[2];
    int  chrPitch       = width>>1;

    if(bSSE2Available)
    {
        __m128i lumMask = _mm_set1_epi32(0x0000FF00);
        __m128i uvMask = _mm_set1_epi16(0x00FF);

        for(int y=startY; y<endY; y+=2)
        {
            int yPos    = y*pitch;
            int chrYPos = ((y>>1)*chrPitch);
            int lumYPos = y*width;

            for(int x=0; x<width; x+=4)
            {
                LPBYTE lpImagePos = input+yPos+(x*4);
                int chrPos  = chrYPos + (x>>1);
                int lumPos0 = lumYPos + x;
                int lumPos1 = lumPos0+width;

                __m128i line1 = _mm_load_si128((__m128i*)lpImagePos);
                __m128i line2 = _mm_load_si128((__m128i*)(lpImagePos+pitch));

                //pack lum vals
                {
                    __m128i packVal = _mm_packs_epi32(_mm_srli_si128(_mm_and_si128(line1, lumMask), 1), _mm_srli_si128(_mm_and_si128(line2, lumMask), 1));
                    packVal = _mm_packus_epi16(packVal, packVal);

                    *(LPUINT)(lumPlane+lumPos0) = packVal.m128i_u32[0];
                    *(LPUINT)(lumPlane+lumPos1) = packVal.m128i_u32[1];
                }

                //do average, pack UV vals
                {
                    __m128i addVal = _mm_add_epi64(_mm_and_si128(line1, uvMask), _mm_and_si128(line2, uvMask));
                    __m128i avgVal = _mm_srai_epi16(_mm_add_epi64(addVal, _mm_shuffle_epi32(addVal, _MM_SHUFFLE(2, 3, 0, 1))), 2);
                    avgVal = _mm_shuffle_epi32(avgVal, _MM_SHUFFLE(3, 1, 2, 0));
                    avgVal = _mm_shufflelo_epi16(avgVal, _MM_SHUFFLE(3, 1, 2, 0));
                    avgVal = _mm_packus_epi16(avgVal, avgVal);

                    DWORD packedVals = avgVal.m128i_u32[0];

                    *(LPWORD)(uPlane+chrPos) = WORD(packedVals);
                    *(LPWORD)(vPlane+chrPos) = WORD(packedVals>>16);
                }
            }
        }
    }
    else
    {
#ifdef _WIN64
        for(int y=startY; y<endY; y+=2)