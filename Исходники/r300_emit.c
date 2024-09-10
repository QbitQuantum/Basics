/* Convert a normal single-precision float into the 7.16 format
 * used by the R300 fragment shader.
 */
uint32_t pack_float24(float f)
{
    union {
        float fl;
        uint32_t u;
    } u;
    float mantissa;
    int exponent;
    uint32_t float24 = 0;

    if (f == 0.0)
        return 0;

    u.fl = f;

    mantissa = frexpf(f, &exponent);

    /* Handle -ve */
    if (mantissa < 0) {
        float24 |= (1 << 23);
        mantissa = mantissa * -1.0;
    }
    /* Handle exponent, bias of 63 */
    exponent += 62;
    float24 |= (exponent << 16);
    /* Kill 7 LSB of mantissa */
    float24 |= (u.u & 0x7FFFFF) >> 7;

    return float24;
}