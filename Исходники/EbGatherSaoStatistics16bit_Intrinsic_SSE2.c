EB_ERRORTYPE GatherSaoStatisticsLcu_OnlyEo_90_45_135_16bit_SSE2_INTRIN(
    EB_U16                   *inputSamplePtr,       // input parameter, source Picture Ptr
    EB_U32                   inputStride,           // input parameter, source stride
    EB_U16                   *reconSamplePtr,       // input parameter, deblocked Picture Ptr
    EB_U32                   reconStride,           // input parameter, deblocked stride
    EB_U32                   lcuWidth,              // input parameter, LCU width
    EB_U32                   lcuHeight,             // input parameter, LCU height
    EB_S32                   eoDiff[SAO_EO_TYPES][SAO_EO_CATEGORIES + 1],    // output parameter, used to store Edge Offset diff, eoDiff[SAO_EO_TYPES] [SAO_EO_CATEGORIES]
    EB_U16                   eoCount[SAO_EO_TYPES][SAO_EO_CATEGORIES + 1])   // output parameter, used to store Edge Offset count, eoCount[SAO_EO_TYPES] [SAO_EO_CATEGORIES]
    // output parameter, used to store Edge Offset count, eoCount[SAO_EO_TYPES] [SAO_EO_CATEGORIES]
{
#define boShift 5

    EB_ERRORTYPE return_error = EB_ErrorNone;
    EB_U64 count_x, count_y;
    EB_S32 diff;
    __m128i xmm0, xmm_1, xmm_N1, xmm_N3, xmm_N4, xmm_skip_mask, xmm9, xmm10, xmm11, xmm12, xmm13, xmm15;
    __m128i xmm_temp_input1, xmm_temp_input2, xmm_temp_recon1, xmm_temp_recon2, xmm_diff1, xmm_diff2;
    __m128i xmm_sign_1, xmm_sign_1a, xmm_sign_1b, xmm_sign_2a, xmm_sign_2b, xmm_sign_2, xmm_eoIndex;

    xmm0 = _mm_setzero_si128();
    xmm12 = _mm_setzero_si128();
    xmm15 = _mm_set1_epi16(0x0001);
    xmm_N1 = _mm_set1_epi8((signed char)0xFF);
    xmm_N3 = _mm_set1_epi8((signed char)0xFD);
    xmm_N4 = _mm_set1_epi8((signed char)0xFC);
    xmm_1 = _mm_sub_epi8(xmm0, xmm_N1);

    // Initialize SAO Arrays
    EB_ALIGN(16) EB_S8 rTemp[512] = { 0 };
    EB_U64 reconStrideTemp;

    lcuHeight -= 2;                          
    inputSamplePtr += inputStride + 1;       
    reconSamplePtr++;                        

    if (lcuWidth == 16) {

        xmm_skip_mask = _mm_srli_si128(xmm_N1, 2);
        for (count_y = 0; count_y < lcuHeight; ++count_y) {

            xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride));
            xmm_temp_recon2 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 8));
            xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr));
            xmm_temp_input2 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 8));
            xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);
            xmm_diff2 = _mm_sub_epi16(xmm_temp_input2, xmm_temp_recon2);

            xmm_diff2 = _mm_slli_si128(xmm_diff2, 4); //skip last 2 samples
            xmm_diff2 = _mm_srli_si128(xmm_diff2, 4); //skip last 2 samples

            // EO-90
            MACRO_CALC_EO_INDEX(reconSamplePtr, reconSamplePtr+2*reconStride)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 2 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

            // EO-135
            MACRO_CALC_EO_INDEX(reconSamplePtr-1, reconSamplePtr+2*reconStride+1)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 2 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

           // EO-45
           MACRO_CALC_EO_INDEX(reconSamplePtr+1, reconSamplePtr+2*reconStride-1)
           xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 2 samples
           MACRO_GATHER_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)
           
           inputSamplePtr += inputStride;
           reconSamplePtr += reconStride;
        }
        lcuWidth = 2;
    }
    else if (lcuWidth == 28) {

        xmm_skip_mask = _mm_srli_si128(xmm_N1, 6);

        for (count_y = 0; count_y < lcuHeight; ++count_y) {
            //----------- 0-15 -----------
            xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride));
            xmm_temp_recon2 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 8));
            xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr));
            xmm_temp_input2 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 8));
            xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);
            xmm_diff2 = _mm_sub_epi16(xmm_temp_input2, xmm_temp_recon2);

            // EO-90
            MACRO_CALC_EO_INDEX(reconSamplePtr, reconSamplePtr+2*reconStride)
            MACRO_GATHER_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

            // EO-135
            MACRO_CALC_EO_INDEX(reconSamplePtr-1, reconSamplePtr+2*reconStride+1)
            MACRO_GATHER_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

            // EO-45
            MACRO_CALC_EO_INDEX(reconSamplePtr+1, reconSamplePtr+2*reconStride-1)
            MACRO_GATHER_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)
            
            //----------- 16-25 -----------
            xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 16));
            xmm_temp_recon2 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 24));
            xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 16));
            xmm_temp_input2 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 24));
            xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);
            xmm_diff2 = _mm_sub_epi16(xmm_temp_input2, xmm_temp_recon2);

            xmm_diff2 = _mm_slli_si128(xmm_diff2, 12); //skip last 6 samples
            xmm_diff2 = _mm_srli_si128(xmm_diff2, 12); //skip last 6 samples

            // EO-90
            MACRO_CALC_EO_INDEX(reconSamplePtr+16, reconSamplePtr+2*reconStride+16)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 6 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

            // EO-135
            MACRO_CALC_EO_INDEX(reconSamplePtr+15, reconSamplePtr+2*reconStride+17)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 6 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

            // EO-45
            MACRO_CALC_EO_INDEX(reconSamplePtr+17, reconSamplePtr+2*reconStride+15)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 6 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)

            inputSamplePtr += inputStride;
            reconSamplePtr += reconStride;
        }
        lcuWidth = 6;
    }
    else if (lcuWidth == 56) {

        xmm_skip_mask = _mm_srli_si128(xmm_N1, 10);
        lcuWidth -= 8;
        inputStride -= lcuWidth;
        reconStrideTemp = reconStride - lcuWidth;

        for (count_y = 0; count_y < lcuHeight; ++count_y) {
            for (count_x = 0; count_x < lcuWidth; count_x += 16) {
                //----------- 0-15 -----------
                xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride));
                xmm_temp_recon2 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 8));
                xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr));
                xmm_temp_input2 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 8));
                xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);
                xmm_diff2 = _mm_sub_epi16(xmm_temp_input2, xmm_temp_recon2);

                // EO-90
                MACRO_CALC_EO_INDEX(reconSamplePtr, reconSamplePtr + 2 * reconStride)
                MACRO_GATHER_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

                // EO-135
                MACRO_CALC_EO_INDEX(reconSamplePtr - 1, reconSamplePtr + 2 * reconStride + 1)
                MACRO_GATHER_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

                // EO-45
                MACRO_CALC_EO_INDEX(reconSamplePtr + 1, reconSamplePtr + 2 * reconStride - 1)
                MACRO_GATHER_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)

                inputSamplePtr += 16;
                reconSamplePtr += 16;                 
            }
            //----------- 48-53 -----------
            xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride));
            xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr));
            xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);

            xmm_diff1 = _mm_slli_si128(xmm_diff1, 4); //skip last 10 samples
            xmm_diff1 = _mm_srli_si128(xmm_diff1, 4); //skip last 10 samples

            // EO-90
            MACRO_CALC_EO_INDEX_HALF(reconSamplePtr, reconSamplePtr+2*reconStride)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 10 samples
            MACRO_GATHER_EO_HALF(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

            // EO-135
            MACRO_CALC_EO_INDEX_HALF(reconSamplePtr-1, reconSamplePtr+2*reconStride+1)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 10 samples
            MACRO_GATHER_EO_HALF(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

            // EO-45
            MACRO_CALC_EO_INDEX_HALF(reconSamplePtr+1, reconSamplePtr+2*reconStride-1)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 10 samples
            MACRO_GATHER_EO_HALF(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)

            inputSamplePtr += inputStride;
            reconSamplePtr += reconStrideTemp;
        }
        lcuWidth = 10;
    }
    else {

        lcuWidth -= 16;
        inputStride -= lcuWidth;
        reconStrideTemp = reconStride - lcuWidth;
        xmm_skip_mask = _mm_srli_si128(xmm_N1, 2);

        for (count_y = 0; count_y < lcuHeight; ++count_y) {
            for (count_x = 0; count_x < lcuWidth; count_x += 16) {
                //----------- 0-15 -----------
                xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride));
                xmm_temp_recon2 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 8));
                xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr));
                xmm_temp_input2 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 8));
                xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);
                xmm_diff2 = _mm_sub_epi16(xmm_temp_input2, xmm_temp_recon2);

                //EO-90
                MACRO_CALC_EO_INDEX(reconSamplePtr, reconSamplePtr + 2 * reconStride)
                MACRO_GATHER_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

                //EO-135
                MACRO_CALC_EO_INDEX(reconSamplePtr - 1, reconSamplePtr + 2 * reconStride + 1)
                MACRO_GATHER_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

                //EO-45
                MACRO_CALC_EO_INDEX(reconSamplePtr + 1, reconSamplePtr + 2 * reconStride - 1)
                MACRO_GATHER_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)

                inputSamplePtr += 16;
                reconSamplePtr += 16;
            }
            //----------- 48-61 -----------
            xmm_temp_recon1 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride));
            xmm_temp_recon2 = _mm_loadu_si128((__m128i *)(reconSamplePtr + reconStride + 8));
            xmm_temp_input1 = _mm_loadu_si128((__m128i *)(inputSamplePtr));
            xmm_temp_input2 = _mm_loadu_si128((__m128i *)(inputSamplePtr + 8));
            xmm_diff1 = _mm_sub_epi16(xmm_temp_input1, xmm_temp_recon1);
            xmm_diff2 = _mm_sub_epi16(xmm_temp_input2, xmm_temp_recon2);

            xmm_diff2 = _mm_slli_si128(xmm_diff2, 4); //skip last 2 samples
            xmm_diff2 = _mm_srli_si128(xmm_diff2, 4); //skip last 2 samples

            // EO-90
            MACRO_CALC_EO_INDEX(reconSamplePtr, reconSamplePtr+2*reconStride)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 2 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1)

            // EO-135
            MACRO_CALC_EO_INDEX(reconSamplePtr-1, reconSamplePtr+2*reconStride+1)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 2 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2)

            // EO-45
            MACRO_CALC_EO_INDEX(reconSamplePtr+1, reconSamplePtr+2*reconStride-1)
            xmm_eoIndex = _mm_and_si128(xmm_eoIndex, xmm_skip_mask); // skip last 2 samples
            MACRO_GATHER_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3)

            inputSamplePtr += inputStride;
            reconSamplePtr += reconStrideTemp;
        }
        lcuWidth = 2;
    }

    lcuWidth = (EB_U16)lcuWidth * (EB_U16)lcuHeight;

    MACRO_SAVE_EO(OFFSET_EO_DIFF_1, OFFSET_EO_COUNT_1, 1)
    MACRO_SAVE_EO(OFFSET_EO_DIFF_2, OFFSET_EO_COUNT_2, 2)
    MACRO_SAVE_EO(OFFSET_EO_DIFF_3, OFFSET_EO_COUNT_3, 3)
                                    
    return return_error;
}