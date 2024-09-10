static t_int *op_perf2(t_int *w) {
	t_triangulator *x = (t_triangulator *)(w[1]);
	t_sample *in = (t_sample *)(w[2]);
	t_sample *out = (t_sample *)(w[3]);
	int n = (int)(w[4]);
	t_float mul = x->invals[0].val;
	t_float add = x->invals[1].val;
	t_sample inter;
	double dphase = x->x_phase + (double)UNITBIT32;
    union tabfudge tf;
    uint32_t casto;
    
    float conv = x->x_conv;
    tf.tf_d = dphase;

    while (n--)
    {
        #ifdef FP_FAST_FMA
        dphase = fma(*in++, conv, dphase);
        #else
        dphase += *in++ * conv;
        #endif
        casto = (uint32_t)tf.tf_i[LOWOFFSET];
        if(casto & 2147483648) /* bit 31 */
        	casto = ~casto;
        inter = (t_sample)casto/1073741823.5 - 1;
        #ifdef FP_FAST_FMA
        *out++ = fma(inter, mul, add);
        #else
        *out++ = inter*mul + add;
        #endif
        tf.tf_d = dphase;
    }
    tf.tf_i[HIOFFSET] = NORMHIPART;
    x->x_phase = tf.tf_d - UNITBIT32;
    return (w+5);
}