		template <bool align> void BgraToBgr(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * bgr, size_t bgrStride)
		{
            assert(width >= A);
            if(align)
                assert(Aligned(bgra) && Aligned(bgraStride) && Aligned(bgr) && Aligned(bgrStride));

            size_t alignedWidth = AlignLo(width, A);
            if(width == alignedWidth)
                alignedWidth -= A;

            __m128i k[3][2];
            k[0][0] = _mm_setr_epi8(0x0, 0x1, 0x2, 0x4, 0x5, 0x6, 0x8, 0x9, 0xA, 0xC, 0xD, 0xE,  -1,  -1,  -1,  -1);
            k[0][1] = _mm_setr_epi8( -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 0x0, 0x1, 0x2, 0x4);
            k[1][0] = _mm_setr_epi8(0x5, 0x6, 0x8, 0x9, 0xA, 0xC, 0xD, 0xE,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1);
            k[1][1] = _mm_setr_epi8( -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 0x0, 0x1, 0x2, 0x4, 0x5, 0x6, 0x8, 0x9);
            k[2][0] = _mm_setr_epi8(0xA, 0xC, 0xD, 0xE,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1);
            k[2][1] = _mm_setr_epi8( -1,  -1,  -1,  -1, 0x0, 0x1, 0x2, 0x4, 0x5, 0x6, 0x8, 0x9, 0xA, 0xC, 0xD, 0xE);

			for(size_t row = 0; row < height; ++row)
			{
                for(size_t col = 0; col < alignedWidth; col += A)
                    BgraToBgrBody<align>(bgra + 4*col, bgr + 3*col, k);
                if(width != alignedWidth)
                    BgraToBgr<false>(bgra + 4*(width - A), bgr + 3*(width - A), k);
                bgra += bgraStride;
                bgr += bgrStride;
			}
		}