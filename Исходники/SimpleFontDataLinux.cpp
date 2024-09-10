PassOwnPtr<SimpleFontData> SimpleFontData::createScaledFontData(const FontDescription& fontDescription, float scaleFactor) const
{
    const float scaledSize = lroundf(fontDescription.computedSize() * scaleFactor);
    return adoptPtr(new SimpleFontData(FontPlatformData(m_platformData, scaledSize), isCustomFont(), false));
}