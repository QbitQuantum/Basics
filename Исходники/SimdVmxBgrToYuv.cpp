        template <bool align> void BgrToYuv420p(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * y, size_t yStride,
            uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
        {
            assert((width % 2 == 0) && (height % 2 == 0) && (width >= DA) && (height >= 2));
            if (align)
            {
                assert(Aligned(y) && Aligned(yStride) && Aligned(u) && Aligned(uStride));
                assert(Aligned(v) && Aligned(vStride) && Aligned(bgr) && Aligned(bgrStride));
            }

            size_t alignedWidth = AlignLo(width, DA);
            const size_t A6 = A * 6;
            for (size_t row = 0; row < height; row += 2)
            {
                Storer<align> _y0(y), _y1(y + yStride), _u(u), _v(v);
                BgrToYuv420p<align, true>(bgr, bgrStride, _y0, _y1, _u, _v);
                for (size_t col = DA, colBgr = A6; col < alignedWidth; col += DA, colBgr += A6)
                    BgrToYuv420p<align, false>(bgr + colBgr, bgrStride, _y0, _y1, _u, _v);
                Flush(_y0, _y1, _u, _v);
                if (width != alignedWidth)
                {
                    size_t offset = width - DA;
                    Storer<false> _y0(y + offset), _y1(y + offset + yStride), _u(u + offset / 2), _v(v + offset / 2);
                    BgrToYuv420p<false, true>(bgr + offset * 3, bgrStride, _y0, _y1, _u, _v);
                    Flush(_y0, _y1, _u, _v);
                }
                y += 2 * yStride;
                u += uStride;
                v += vStride;
                bgr += 2 * bgrStride;
            }
        }