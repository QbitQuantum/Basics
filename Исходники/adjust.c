static float vlc_to_vdp_hue(float hue)
{
    float dummy;

    hue /= 360.f;
    hue = modff(hue, &dummy);
    if (hue > .5f)
        hue -= 1.f;
    return hue * (float)(2. * M_PI);
}