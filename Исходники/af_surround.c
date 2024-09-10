static void filter_2_1(AVFilterContext *ctx)
{
    AudioSurroundContext *s = ctx->priv;
    float *srcl, *srcr, *srclfe;
    int n;

    srcl = (float *)s->input->extended_data[0];
    srcr = (float *)s->input->extended_data[1];
    srclfe = (float *)s->input->extended_data[2];

    for (n = 0; n < s->buf_size; n++) {
        float l_re = srcl[2 * n], r_re = srcr[2 * n];
        float l_im = srcl[2 * n + 1], r_im = srcr[2 * n + 1];
        float lfe_re = srclfe[2 * n], lfe_im = srclfe[2 * n + 1];
        float c_phase = atan2f(l_im + r_im, l_re + r_re);
        float l_mag = hypotf(l_re, l_im);
        float r_mag = hypotf(r_re, r_im);
        float l_phase = atan2f(l_im, l_re);
        float r_phase = atan2f(r_im, r_re);
        float phase_dif = fabsf(l_phase - r_phase);
        float mag_dif = (l_mag - r_mag) / (l_mag + r_mag);
        float mag_total = hypotf(l_mag, r_mag);
        float x, y;

        if (phase_dif > M_PI)
            phase_dif = 2 * M_PI - phase_dif;

        stereo_position(mag_dif, phase_dif, &x, &y);

        s->upmix_2_1(ctx, l_phase, r_phase, c_phase, mag_total, lfe_re, lfe_im, x, y, n);
    }
}