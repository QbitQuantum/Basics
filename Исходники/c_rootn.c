DLLEXPORT float rootnf(float x, int y)
{
    int y_odd  = (y&1);
    int y_even = !y_odd;
    int y_neg  = (y<0);
    int x_neg  = (x<0);

    if (y == 0) return NANF;
    if (EXPF(x) == 0)  /* Flush denormalized input to zero */
        return (y > 0) ? 0.0f : (y_even ? INFF : copysign(INFF, x));
    if (y == 1) return x;
    if (ISNEGINFF(x) && y_even) return NANF;
    if (ISINFF(x)) return y_neg ? copysign(0.0f, x) : x;
    if (ISANYZEROF(x) && y_odd && y_neg) return copysign(INFF, x);

    int negresult = 0;
    if (x_neg && y_odd) { negresult = 1; x = FABSF(x); }

    float result =  powf(x, reciprocalf(y));
    if (negresult) result = -result;
    return result;
}