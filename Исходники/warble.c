static uint64_t make_float64(int32_t sample, int shift)
{
    /* TODO: be more portable */
    double val = ldexp(sample, -shift);
    return *(uint64_t*)&val;
}