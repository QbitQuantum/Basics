        template <bool even> void ReduceGray4x4(const uint8_t *src, size_t srcWidth, size_t srcHeight, size_t srcStride,
            uint8_t *dst, size_t dstWidth, size_t dstHeight, size_t dstStride)
        {
            assert((srcWidth + 1) / 2 == dstWidth && (srcHeight + 1) / 2 == dstHeight && srcWidth > A);

            size_t alignedDstWidth = Simd::AlignLo(dstWidth, HA);
            size_t srcTail = Simd::AlignHi(srcWidth - A, 2);

            Buffer buffer(Simd::AlignHi(dstWidth, A));

            __m128i tmp = ReduceColNose(src);
            Store<true>((__m128i*)buffer.src0, tmp);
            Store<true>((__m128i*)buffer.src1, tmp);
            size_t srcCol = A, dstCol = HA;
            for (; srcCol < srcWidth - A; srcCol += A, dstCol += HA)
            {
                tmp = ReduceColBody(src + srcCol);
                Store<true>((__m128i*)(buffer.src0 + dstCol), tmp);
                Store<true>((__m128i*)(buffer.src1 + dstCol), tmp);
            }
            tmp = ReduceColTail<even>(src + srcTail);
            Store<false>((__m128i*)(buffer.src0 + dstWidth - HA), tmp);
            Store<false>((__m128i*)(buffer.src1 + dstWidth - HA), tmp);

            for (size_t row = 0; row < srcHeight; row += 2, dst += dstStride)
            {
                const uint8_t *src2 = src + srcStride*(row + 1);
                const uint8_t *src3 = src2 + srcStride;
                if (row >= srcHeight - 2)
                {
                    src2 = src + srcStride*(srcHeight - 1);
                    src3 = src2;
                }

                Store<true>((__m128i*)buffer.src2, ReduceColNose(src2));
                Store<true>((__m128i*)buffer.src3, ReduceColNose(src3));
                size_t srcCol = A, dstCol = HA;
                for (; srcCol < srcWidth - A; srcCol += A, dstCol += HA)
                {
                    Store<true>((__m128i*)(buffer.src2 + dstCol), ReduceColBody(src2 + srcCol));
                    Store<true>((__m128i*)(buffer.src3 + dstCol), ReduceColBody(src3 + srcCol));
                }
                Store<false>((__m128i*)(buffer.src2 + dstWidth - HA), ReduceColTail<even>(src2 + srcTail));
                Store<false>((__m128i*)(buffer.src3 + dstWidth - HA), ReduceColTail<even>(src3 + srcTail));

                for (size_t col = 0; col < alignedDstWidth; col += HA)
                    _mm_storel_epi64((__m128i*)(dst + col), ReduceRow<true>(buffer, col));

                if (alignedDstWidth != dstWidth)
                    _mm_storel_epi64((__m128i*)(dst + dstWidth - HA), ReduceRow<false>(buffer, dstWidth - HA));

                Swap(buffer.src0, buffer.src2);
                Swap(buffer.src1, buffer.src3);
            }
        }