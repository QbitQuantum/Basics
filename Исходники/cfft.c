static void passf2pos_sse_ido(const uint16_t ido, const uint16_t l1, const complex_t *cc,
                              complex_t *ch, const complex_t *wa)
{
    uint16_t i, k, ah, ac;

    for (k = 0; k < l1; k++)
    {
        ah = k*ido;
        ac = 2*k*ido;

        for (i = 0; i < ido; i+=4)
        {
            __m128 m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14;
            __m128 m15, m16, m17, m18, m19, m20, m21, m22, m23, m24;
            __m128 w1, w2, w3, w4;

            m1 = _mm_load_ps(&RE(cc[ac+i]));
            m2 = _mm_load_ps(&RE(cc[ac+ido+i]));
            m5 = _mm_load_ps(&RE(cc[ac+i+2]));
            m6 = _mm_load_ps(&RE(cc[ac+ido+i+2]));
            w1 = _mm_load_ps(&RE(wa[i]));
            w3 = _mm_load_ps(&RE(wa[i+2]));

            m3 = _mm_add_ps(m1, m2);
            m15 = _mm_add_ps(m5, m6);

            m4 = _mm_sub_ps(m1, m2);
            m16 = _mm_sub_ps(m5, m6);

            _mm_store_ps(&RE(ch[ah+i]), m3);
            _mm_store_ps(&RE(ch[ah+i+2]), m15);


            w2 = _mm_shuffle_ps(w1, w1, _MM_SHUFFLE(2, 3, 0, 1));
            w4 = _mm_shuffle_ps(w3, w3, _MM_SHUFFLE(2, 3, 0, 1));

            m7 = _mm_mul_ps(m4, w1);
            m17 = _mm_mul_ps(m16, w3);
            m8 = _mm_mul_ps(m4, w2);
            m18 = _mm_mul_ps(m16, w4);

            m9  = _mm_shuffle_ps(m7, m8, _MM_SHUFFLE(2, 0, 2, 0));
            m19 = _mm_shuffle_ps(m17, m18, _MM_SHUFFLE(2, 0, 2, 0));
            m10 = _mm_shuffle_ps(m7, m8, _MM_SHUFFLE(3, 1, 3, 1));
            m20 = _mm_shuffle_ps(m17, m18, _MM_SHUFFLE(3, 1, 3, 1));

            m11 = _mm_add_ps(m9, m10);
            m21 = _mm_add_ps(m19, m20);
            m12 = _mm_sub_ps(m9, m10);
            m22 = _mm_sub_ps(m19, m20);

            m13 = _mm_shuffle_ps(m11, m11, _MM_SHUFFLE(0, 0, 3, 2));
            m23 = _mm_shuffle_ps(m21, m21, _MM_SHUFFLE(0, 0, 3, 2));

            m14 = _mm_unpacklo_ps(m12, m13);
            m24 = _mm_unpacklo_ps(m22, m23);

            _mm_store_ps(&RE(ch[ah+i+l1*ido]), m14);
            _mm_store_ps(&RE(ch[ah+i+2+l1*ido]), m24);
        }
    }
}