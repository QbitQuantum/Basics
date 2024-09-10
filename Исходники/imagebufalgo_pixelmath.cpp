inline float rangecompress (float x)
{
    // Formula courtesy of Sony Pictures Imageworks
    const float x1 = 1.0, a = 1.2607481479644775391;
    const float b = 0.28785100579261779785, c = -1.4042005538940429688;
    float absx = fabsf(x);
    if (absx <= x1)
        return x;
    return copysignf (a + b * logf(fabsf(c*absx + 1.0f)), x);
}