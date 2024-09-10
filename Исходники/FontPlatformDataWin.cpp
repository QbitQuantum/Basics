FontPlatformData& FontPlatformData::operator=(const FontPlatformData& data)
{
    if (this != &data) {
        m_textSize = data.m_textSize;
        m_fakeBold = data.m_fakeBold;
        m_fakeItalic = data.m_fakeItalic;
        m_orientation = data.m_orientation;
        m_typeface = data.m_typeface;
        m_paintTextFlags = data.m_paintTextFlags;

#if !USE(HARFBUZZ)
        m_font = data.m_font;
        // The following fields will get re-computed if necessary.
        ScriptFreeCache(&m_scriptCache);
        m_scriptCache = 0;
        m_scriptFontProperties.clear();
#endif
    }
    return *this;
}