static void compute_step_tv_inner_simd(unsigned w, unsigned h, unsigned nchannel, struct aux auxs[nchannel], unsigned x, unsigned y, double *tv) {
        const __m128 minf = _mm_set_ps1(INFINITY);
        const __m128 mzero = _mm_set_ps1(0.);

        __m128 g_xs[3] = {0};
        __m128 g_ys[3] = {0};
        for(unsigned c = 0; c < nchannel; c++) {
                struct aux *aux = &auxs[c];
                __m128 here = _mm_load_ps(p(aux->fdata, x, y, w, h));
                // forward gradient x
                g_xs[c] = _mm_loadu_ps(p(aux->fdata, x+1, y, w, h)) - here;
                // forward gradient y
                g_ys[c] = _mm_loadu_ps(p(aux->fdata, x, y+1, w, h)) - here;
        }
        // norm
        __m128 g_norm = mzero;
        for(unsigned c = 0; c < nchannel; c++) {
                g_norm += SQR(g_xs[c]);
                g_norm += SQR(g_ys[c]);
        }
        g_norm = _mm_sqrt_ps(g_norm);

        float alpha = 1./sqrtf(nchannel);
        *tv += alpha * g_norm[0];
        *tv += alpha * g_norm[1];
        *tv += alpha * g_norm[2];
        *tv += alpha * g_norm[3];

        __m128 malpha = _mm_set_ps1(alpha);

        // set zeroes to infinity
        g_norm = _mm_or_ps(g_norm, _mm_and_ps(minf, _mm_cmpeq_ps(g_norm, mzero)));

        // compute derivatives
        for(unsigned c = 0; c < nchannel; c++) {
                __m128 g_x = g_xs[c];
                __m128 g_y = g_ys[c];
                struct aux *aux = &auxs[c];

                // N.B. for numerical stability and same exact result as the c version,
                // we must calculate the objective gradient at x+1 before x
                {
                        float *pobj_r = p(aux->obj_gradient, x+1, y, w, h);
                        __m128 obj_r = _mm_loadu_ps(pobj_r);
                        obj_r += malpha * g_x / g_norm;
                        _mm_storeu_ps(pobj_r, obj_r);
                }

                {
                        float *pobj = p(aux->obj_gradient, x, y, w, h);
                        __m128 obj = _mm_load_ps(pobj);
                        obj += malpha * -(g_x + g_y) / g_norm;
                        _mm_store_ps(pobj, obj);
                }

                {
                        float *pobj_b = p(aux->obj_gradient, x, y+1, w, h);
                        __m128 obj_b = _mm_load_ps(pobj_b);
                        obj_b += malpha * g_y / g_norm;
                        _mm_store_ps(pobj_b, obj_b);
                }
        }
        // store
        for(unsigned c = 0; c < nchannel; c++) {
                struct aux *aux = &auxs[c];
                _mm_store_ps(p(aux->temp[0], x, y, w, h), g_xs[c]);
                _mm_store_ps(p(aux->temp[1], x, y, w, h), g_ys[c]);
        }
}