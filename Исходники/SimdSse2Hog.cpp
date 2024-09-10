        template <bool align> SIMD_INLINE void HogDirectionHistograms(const __m128 & dx, const __m128 & dy, Buffer & buffer, size_t col)
        {
            __m128 bestDot = _mm_setzero_ps();
            __m128i bestIndex = _mm_setzero_si128();
            for(int i = 0; i < buffer.size; ++i)
            {
                __m128 dot = _mm_add_ps(_mm_mul_ps(dx, buffer.cos[i]), _mm_mul_ps(dy, buffer.sin[i]));
                __m128 mask = _mm_cmpgt_ps(dot, bestDot);
                bestDot = _mm_max_ps(dot, bestDot);
                bestIndex = Combine(_mm_castps_si128(mask), buffer.pos[i], bestIndex);

                dot = _mm_sub_ps(_mm_setzero_ps(), dot);
                mask = _mm_cmpgt_ps(dot, bestDot);
                bestDot = _mm_max_ps(dot, bestDot);
                bestIndex = Combine(_mm_castps_si128(mask), buffer.neg[i], bestIndex);
            }
            Store<align>((__m128i*)(buffer.index + col), bestIndex);
            Sse::Store<align>(buffer.value + col, _mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(dx, dx), _mm_mul_ps(dy, dy))));
        }