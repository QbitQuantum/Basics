void
plot(u32 w, u32 h, float x1, float y1, float x2, float y2, float dx,
        float dy, u32 max_iter = 4096)
{
    assert(w % 8 == 0);

    // AVX Constants
    float const constants[] {
        x1,
        y1,
        dx,
        dy,
        1.0f,
        4.0f
    };

    __m256 const vx1 = _mm256_broadcast_ss(constants);
    __m256 const vy1 = _mm256_broadcast_ss(constants + 1);
    __m256 const vdx = _mm256_broadcast_ss(constants + 2);
    __m256 const vdy = _mm256_broadcast_ss(constants + 3);
    __m256 const v1 = _mm256_broadcast_ss(constants + 4);
    __m256 const v4 = _mm256_broadcast_ss(constants + 5);

    // Start timing
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
    std::chrono::duration<double> dt;
    t1 = std::chrono::high_resolution_clock::now();

    // Zero line counter
    __m256 vj = _mm256_xor_ps(v1, v1);

    for (u32 j = 0; j < h; j++) {
        for (u32 i = 0; i < w; i += 8) {

            // Fill column counter
            float const vi_[8] { i+0.f, i+1.f, i+2.f, i+3.f, i+4.f, i+5.f, i+6.f, i+7.f };
            __m256 vi = _mm256_load_ps(vi_);

            // Compute start point
            __m256 vx0 = _mm256_mul_ps(vi, vdx);
            vx0 = _mm256_add_ps(vx0, vx1);
            __m256 vy0 = _mm256_mul_ps(vj, vdy);
            vy0 = _mm256_add_ps(vy0, vy1);

            __m256 vx = vx0;
            __m256 vy = vy0;

            __m256 vcount = _mm256_xor_ps(v1, v1);  // Zero iteration counter

            u32 iter        = 0;
            u8  no_overflow = 0;
            do {
                // Compute products
                __m256 vxx = _mm256_mul_ps(vx, vx);
                __m256 vyy = _mm256_mul_ps(vy, vy);

                // Check termination condition
                __m256 vtmp = _mm256_add_ps(vxx, vyy);
                vtmp = _mm256_cmp_ps(vtmp, v4, _CMP_LT_OQ);
                no_overflow = _mm256_movemask_ps(vtmp) & 0xff;

                // Accumulate iteration counter
                vtmp = _mm256_and_ps(vtmp, v1);
                vcount = _mm256_add_ps(vcount, vtmp);

                // Step
                vtmp = _mm256_mul_ps(vx, vy);
                vtmp = _mm256_add_ps(vtmp, vtmp);
                vy = _mm256_add_ps(vtmp, vy0);
                vtmp = _mm256_sub_ps(vxx, vyy);
                vx = _mm256_add_ps(vtmp, vx0);
                ++iter;

            } while (no_overflow && (iter < max_iter));

            for (u32 k = 0; k < 8; k++) {
                u32 n = ((float *) &vcount)[k] + 0.5f;
                if (n == max_iter) n = 0;

                char c = ' ';
                if (n > 0) {
                    static char const charset[] = ".,c8M@jawrpogOQEPGJ";
                    c = charset[n % (sizeof(charset) - 1)];
                }

                attron(COLOR_PAIR((n % 7) + 1));
                addch(c);
                attroff(COLOR_PAIR((n % 7) + 1));
                if (i + k + 1 == w) addch('\n');
            }
        }

        // Increment line counter
        vj = _mm256_add_ps(vj, v1);
    }

    // End timing
    t2 = std::chrono::high_resolution_clock::now();
    dt = t2 - t1;
    std::string info = std::to_string(dt.count() * 1000.0) + "ms";

    attron(COLOR_PAIR(1));
    printw(info.c_str());
    attroff(COLOR_PAIR(1));
}