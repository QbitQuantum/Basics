static inline void calc_lbp_16_strip(IplImage * src, IplImage * dst, unsigned base)
{
    const signed char* src_data = (signed char*)(src->imageData + base);
    unsigned char * dst_data = (unsigned char*)(dst->imageData + base);
    const signed char* const src_end = (signed char*)src->imageData + (src->height-1) * src->widthStep;
   
    __m128i pixels[3];

    // Load first two rows
    //pixels[0] = *(__m128i*)src_data;//_mm_set_epi64(*(__m64*)(src_data+8), *(__m64*)(src_data));
    pixels[0] = _mm_set_epi64(*(__m64*)(src_data+8), *(__m64*)(src_data));
    //pixels[0] = _mm_xor_si128(pixels[0], sign_bit.q); // conversion from unsigned to signed - invert sign bit
    src_data += src->widthStep;
    //pixels[1] = *(__m128i*)src_data;//_mm_set_epi64(*(__m64*)(src_data+8), *(__m64*)(src_data));
    pixels[1] = _mm_set_epi64(*(__m64*)(src_data+8), *(__m64*)(src_data));
    //pixels[1] = _mm_xor_si128(pixels[1], sign_bit.q);
    src_data += src->widthStep;

    int phase = 2;

    __m128i * phase_map[3][3] = {
        {pixels+1, pixels+2, pixels},
        {pixels+2, pixels, pixels+1},
        {pixels, pixels+1, pixels+2},
    };

    while (src_data < src_end)
    {
        register __m128i weight = ones.q;
        register __m128i code = _mm_setzero_si128();

        //pixels[phase] = _mm_set_epi64(*(__m64*)(src_data+8), *(__m64*)(src_data));
        //pixels[phase] = _mm_xor_si128(pixels[phase], sign_bit.q);
        //pixels[phase] = _mm_xor_si128(_mm_lddqu_si128((__m128i*)src_data), sign_bit.q);
        pixels[phase] = _mm_lddqu_si128((__m128i*)src_data);

        src_data += src->widthStep;
        dst_data += dst->widthStep;
        
        _mm_prefetch(src_data, _MM_HINT_T0);

        register __m128i a = *(phase_map[phase][0]);
        register __m128i b = *(phase_map[phase][1]);
        register __m128i c = *(phase_map[phase][2]);

        phase++;
        phase = (phase == 3) ? 0 : phase;
        
        // X . .   A
        // . o .   B
        // . . .   C
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, _mm_slli_si128(a, 1)), weight));
        weight = _mm_slli_epi64(weight, 1);

        // . X .
        // .   .
        // . . .
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, a), weight));
        weight = _mm_slli_epi64(weight, 1);
        
        // . . X
        // .   .
        // . . .
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, _mm_srli_si128(a, 1)), weight));
        weight = _mm_slli_epi64(weight, 1);

        // . . .
        // .   X
        // . . .
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, _mm_srli_si128(b, 1)), weight));
        weight = _mm_slli_epi64(weight, 1);
        
        // . . .
        // .   .
        // . . X
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, _mm_srli_si128(c, 1)), weight));
        weight = _mm_slli_epi64(weight, 1);

        // . . .
        // .   .
        // . X .
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, c), weight));
        weight = _mm_slli_epi64(weight, 1);
        
        // . . .
        // .   .
        // X . .
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, _mm_slli_si128(c, 1)), weight));
        weight = _mm_slli_epi64(weight, 1);
        
        // . . .
        // X   .
        // . . .
        code = _mm_or_si128(code, _mm_and_si128(_mm_cmplt_epi8(b, _mm_slli_si128(b, 1)), weight)); 

        _mm_maskmoveu_si128(code, lbp_valid_mask.q, (char*)dst_data); // store the results - unaligned write
    }
}