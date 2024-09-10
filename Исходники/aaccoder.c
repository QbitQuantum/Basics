static inline int log2f_ceil(float x)
{
    int exp;
    float norm = frexpf(x, &exp);
    if (norm > 0.5f)
        return exp;
    return exp-1;
}