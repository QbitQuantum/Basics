        template <bool align> void Bgr48pToBgra32(const uint8_t * blue, size_t blueStride, size_t width, size_t height,
            const uint8_t * green, size_t greenStride, const uint8_t * red, size_t redStride, uint8_t * bgra, size_t bgraStride, uint8_t alpha)
        {
            assert(width >= HA);
            if(align)
            {
                assert(Aligned(blue) && Aligned(blueStride));
                assert(Aligned(green) && Aligned(greenStride));
                assert(Aligned(red) && Aligned(redStride));
                assert(Aligned(bgra) && Aligned(bgraStride));
            }

            __m128i _alpha = _mm_slli_si128(_mm_set1_epi16(alpha), 1);
            size_t alignedWidth = AlignLo(width, HA);
            for(size_t row = 0; row < height; ++row)
            {
                for(size_t col = 0, srcOffset = 0, dstOffset = 0; col < alignedWidth; col += HA, srcOffset += A, dstOffset += DA)
                    Bgr48pToBgra32<align>(bgra + dstOffset, blue, green, red, srcOffset, _alpha);
                if(width != alignedWidth)
                    Bgr48pToBgra32<false>(bgra + (width - HA)*4, blue, green, red, (width - HA)*2, _alpha);
                blue += blueStride;
                green += greenStride;
                red += redStride;
                bgra += bgraStride;
            }
        }