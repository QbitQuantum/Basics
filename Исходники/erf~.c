static t_int *erf_perform(t_int *w)
{
    t_float *in = (t_float *)(w[1]);
    t_float *out = (t_float *)(w[2]);
    int n = (int)(w[3]);

    while (n--)
        *out++ = erff(*in++);

    return w+4;
}