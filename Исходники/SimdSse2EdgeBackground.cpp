        template <bool align> void EdgeBackgroundAdjustRangeMasked(uint8_t * backgroundCount, size_t backgroundCountStride, size_t width, size_t height, 
             uint8_t * backgroundValue, size_t backgroundValueStride, uint8_t threshold, const uint8_t * mask, size_t maskStride)
        {
            assert(width >= A);
            if(align)
            {
                assert(Aligned(backgroundValue) && Aligned(backgroundValueStride));
                assert(Aligned(backgroundCount) && Aligned(backgroundCountStride));
                assert(Aligned(mask) && Aligned(maskStride));
            }

            const __m128i _threshold = _mm_set1_epi8((char)threshold);
            size_t alignedWidth = AlignLo(width, A);
            __m128i tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
            for(size_t row = 0; row < height; ++row)
            {
                for(size_t col = 0; col < alignedWidth; col += A)
                    EdgeBackgroundAdjustRangeMasked<align>(backgroundCount, backgroundValue, mask, col, _threshold, K8_01);
                if(alignedWidth != width)
                    EdgeBackgroundAdjustRangeMasked<false>(backgroundCount, backgroundValue, mask, width - A, _threshold, tailMask);
                backgroundValue += backgroundValueStride;
                backgroundCount += backgroundCountStride;
                mask += maskStride;
            }		
        }