static t_int *atanh_perform(t_int *w)
{
    int nblock = (int)(w[1]);
    t_float *in = (t_float *)(w[2]);
    t_float *out = (t_float *)(w[3]);
    while (nblock--)
    {
        float f = *in++;
        *out++ = atanhf(f);  /* CHECKME no protection against NaNs */
    }
    return (w + 4);
}