static float get_float(GetBitContext *gb)
{
    int power = get_bits(gb, 5);
    float f = ldexpf(get_bits_long(gb, 23), power - 23);
    if (get_bits1(gb))
        f = -f;
    return f;
}