// based on exiftool's Image::ExifTool::Canon::CanonEv
static float canonEv(const long in) {
    // remove sign
    long val = abs(in);
    // remove fraction
    float frac = static_cast<float>(val & 0x1f);
    val -= long(frac);
    // convert 1/3 (0x0c) and 2/3 (0x14) codes
    if (frac == 0x0c) {
        frac = 32.0f / 3;
    }
    else if (frac == 0x14) {
        frac = 64.0f / 3;
    }
    return copysignf((val + frac) / 32.0f, in);
}