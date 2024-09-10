double dB_to_scale(double dB)
{
    assert(isfinite(dB) || (dB == -INFINITY));
    return exp2(dB / 6.0);
}