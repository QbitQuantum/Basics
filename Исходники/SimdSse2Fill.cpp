        template <bool align> void FillBgr(uint8_t * dst, size_t stride, size_t width, size_t height, uint8_t blue, uint8_t green, uint8_t red)
        {
            size_t size = width*3;
            size_t step = A*3;
            size_t alignedSize = AlignLo(width, A)*3;

            uint32_t bgrb = uint32_t(blue) | (uint32_t(green) << 8) | (uint32_t(red) << 16) | (uint32_t(blue) << 24);
            uint32_t grbg = uint32_t(green) | (uint32_t(red) << 8) | (uint32_t(blue) << 16) | (uint32_t(green) << 24);
            uint32_t rbgr = uint32_t(red) | (uint32_t(blue) << 8) | (uint32_t(green) << 16) | (uint32_t(red) << 24);

            __m128i bgrs[3];
            bgrs[0] = _mm_setr_epi32(bgrb, grbg, rbgr, bgrb);
            bgrs[1] = _mm_setr_epi32(grbg, rbgr, bgrb, grbg);
            bgrs[2] = _mm_setr_epi32(rbgr, bgrb, grbg, rbgr);
            for(size_t row = 0; row < height; ++row)
            {
                size_t offset = 0;
                for(; offset < alignedSize; offset += step)
                {
                    Store<align>((__m128i*)(dst + offset) + 0, bgrs[0]);
                    Store<align>((__m128i*)(dst + offset) + 1, bgrs[1]);
                    Store<align>((__m128i*)(dst + offset) + 2, bgrs[2]);
                }
                if(offset < size)
                {
                    offset = size - step;
                    Store<false>((__m128i*)(dst + offset) + 0, bgrs[0]);
                    Store<false>((__m128i*)(dst + offset) + 1, bgrs[1]);
                    Store<false>((__m128i*)(dst + offset) + 2, bgrs[2]);
                }
                dst += stride;
            }
        }