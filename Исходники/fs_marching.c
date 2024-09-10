        float t[4];
        uint32_t offset = 0;

        float const d[2] = { line[2] - line[0], line[3] - line[1], };
        float const length_inv = 1.0f/sqrtf(d[0]*d[0] + d[1]*d[1]);
        float const n[2] = { d[1]*length_inv, -d[0]*length_inv, };
        float const distance = line[0]*n[0] + line[1]*n[1];

        /* TODO: investigate integer registers */
        __m128 const distance_4 = _mm_set1_ps(distance);
        __m128 const n0_4 = _mm_set1_ps(n[0]);
        __m128 const n1_4 = _mm_set1_ps(n[1]);

        __m128 const mask1_4 = _mm_set1_ps(1);
        __m128 const mask2_4 = _mm_set1_ps(2);
        __m128 const shift_4 = _mm_setr_ps(1, 3, 9, 27);

        /* process cell ids */
        for (uint32_t ii = cells_offset; ii < cells_count; ++ii) {
                uint32_t const id = cells[ii];

                if (id > dims[0]*dims[1]*dims[2]) {
                        printf("big id %u\n", id);
                        assert(0);
                }

                /* get coordinates of cell */
                /* cell grid is one less than data grid */
                uint32_t const i = id%dims[0];
                uint32_t const j = (id/dims[0])%dims[1];
                uint32_t const k = id/(dims[0]*dims[1]);