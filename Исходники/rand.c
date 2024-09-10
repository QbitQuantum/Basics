        inline int rand() {
            __m128i split;
            __m128i multi;
            __m128i adder;
            __m128i mmask;
            __m128i smask;
            __m128i store;

            DATA(multi)={0x000343FD,0x000043FD,0x000343FD,0x00010DCD};
            DATA(adder)={0x00269EC3,0x009E9EC3,0x00D19EC3,0x00000001};
            DATA(mmask)={0xFFFFFFFF,0x00000000,0xFFFFFFFF,0x00000000};
            DATA(smask)={0x00007FFF,0x00007FFF,0x00007FFF,0x00007FFF};
            #undef DATA

            adder = _mm_load_si128   ((__m128i*)data_adder);
            multi = _mm_load_si128   ((__m128i*)data_multi);
            mmask = _mm_load_si128   ((__m128i*)data_mmask);
            smask = _mm_load_si128   ((__m128i*)data_smask);

            split = _mm_shuffle_epi32(
                __ccaprice_stdlib_rseed,
                __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            );

            __ccaprice_stdlib_rseed = _mm_mul_epu32(__ccaprice_stdlib_rseed, multi);
            multi                   = _mm_shuffle_epi32(
                multi,
                __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            );
            split                   = _mm_mul_epu32(split, multi);
            __ccaprice_stdlib_rseed = _mm_and_si128(__ccaprice_stdlib_rseed, mmask);
            split                   = _mm_and_si128(split, mmask);
            split                   = _mm_shuffle_epi32(
                split,
                __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            );
            __ccaprice_stdlib_rseed = _mm_or_si128  (__ccaprice_stdlib_rseed, split);
            __ccaprice_stdlib_rseed = _mm_add_epi32 (__ccaprice_stdlib_rseed, adder);
            store                   = _mm_srai_epi32(__ccaprice_stdlib_rseed, 0x10);
            store                   = _mm_and_si128 (store, smask);

            return (unsigned int)_mm_cvtsi128_si32(store);

            #undef __CCAPRICE_STDLIB_RANDOM_SSE_SHUFFLE
            #undef __CCAPRICE_STDLIB_RANDOM_SSE_STAIRS2
            #undef __CCAPRICE_STDLIB_RANDOM_SSE_STAIRS1
        }