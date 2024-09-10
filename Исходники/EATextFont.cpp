bool FontDescription::operator==(const FontDescription& fd) const
{
    return  (mfSize   == fd.mfSize) &&
            (mStyle   == fd.mStyle) &&
            (mfWeight == fd.mfWeight) &&
            (mSmooth  == fd.mSmooth) &&
            (Stricmp(mFamily, fd.mFamily) == 0) &&
            (mEffect  == fd.mEffect);

    // We currently leave out the following, which isn't entirely correct, but is
    // more efficient. It turns out that we can leave these out very often because
    // the above entities will already uniquely identify the font in most cases.
    //    float     mfStretch;
    //    Pitch     mPitch;
    //    Variant   mVariant;
    //    float     mfEffectX;
    //    float     mfEffectY;
    //    Color     mEffectBaseColor;
    //    Color     mEffectColor;
    //    Color     mHighLightColor;
}