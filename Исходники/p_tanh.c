void generate_ref(float *out, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++)
        out[i] = tanhf(ai[i]);
}