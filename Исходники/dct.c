static void ff_dct_calc_I_c(DCTContext *ctx, FFTSample *data)
{
    int n = 1 << ctx->nbits;
    int i;
    float next = -0.5f * (data[0] - data[n]);

    for (i = 0; i < n / 2; i++) {
        float tmp1 = data[i];
        float tmp2 = data[n - i];
        float s    = SIN(ctx, n, 2 * i);
        float c    = COS(ctx, n, 2 * i);

        c *= tmp1 - tmp2;
        s *= tmp1 - tmp2;

        next += c;

        tmp1        = (tmp1 + tmp2) * 0.5f;
        data[i]     = tmp1 - s;
        data[n - i] = tmp1 + s;
    }

    ctx->rdft.rdft_calc(&ctx->rdft, data);
    data[n] = data[1];
    data[1] = next;

    for (i = 3; i <= n; i += 2)
        data[i] = data[i - 2] - data[i];
}