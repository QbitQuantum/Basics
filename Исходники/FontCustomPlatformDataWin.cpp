FontCustomPlatformData::~FontCustomPlatformData()
{
    if (m_fontReference)
        RemoveFontMemResourceEx(m_fontReference);
}