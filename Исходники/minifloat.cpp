float float_from_gain(gain_minifloat_t a)
{
    int mantissa = a & MANTISSA_MAX;
    int exponent = (a >> MANTISSA_BITS) & EXPONENT_MAX;
    return ldexpf((exponent > 0 ? HIDDEN_BIT | mantissa : mantissa << 1) / ONE_FLOAT,
                  exponent - EXCESS);
}