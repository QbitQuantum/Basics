        // Unroll 4x, interleave bytes, use pmaddubsw (all_x is small)
        while (count > 3) {
            count -= 4;

            int x0[4];
            int x1[4];
            __m128i all_x, sixteen_minus_x;
            PrepareConstantsTwoPixelPairs(xy, mask_3FFF, mask_000F,
                                          sixteen_8bit, mask_dist_select,
                                          &all_x, &sixteen_minus_x, x0, x1);
            xy += 4;

            // First pair of pixel pairs
            // (4x(x1, 16-x1), 4x(x0, 16-x0))
            __m128i scale_x;
            scale_x = _mm_unpacklo_epi8(sixteen_minus_x, all_x);

            __m128i sum0 = ProcessTwoPixelPairs<has_alpha>(
                row0, row1, x0, x1,
                scale_x, all_y, neg_y, alpha);

            // second pair of pixel pairs
            // (4x (x3, 16-x3), 4x (16-x2, x2))
            scale_x = _mm_unpackhi_epi8(sixteen_minus_x, all_x);

            __m128i sum1 = ProcessTwoPixelPairs<has_alpha>(
                row0, row1, x0 + 2, x1 + 2,
                scale_x, all_y, neg_y, alpha);

            // Do the final packing of the two results
