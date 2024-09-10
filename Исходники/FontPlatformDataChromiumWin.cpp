SCRIPT_FONTPROPERTIES* FontPlatformData::scriptFontProperties() const
{
    if (!m_scriptFontProperties) {
        m_scriptFontProperties = new SCRIPT_FONTPROPERTIES;
        memset(m_scriptFontProperties, 0, sizeof(SCRIPT_FONTPROPERTIES));
        m_scriptFontProperties->cBytes = sizeof(SCRIPT_FONTPROPERTIES);
        HRESULT result = ScriptGetFontProperties(0, scriptCache(),
                                                 m_scriptFontProperties);
        if (result == E_PENDING) {
            HWndDC dc(0);
            HGDIOBJ oldFont = SelectObject(dc, hfont());
            HRESULT hr = ScriptGetFontProperties(dc, scriptCache(),
                                                 m_scriptFontProperties);
            if (S_OK != hr) {
                if (PlatformSupport::ensureFontLoaded(hfont())) {
                    // FIXME: Handle gracefully the error if this call also fails.
                    hr = ScriptGetFontProperties(dc, scriptCache(),
                                                 m_scriptFontProperties);
                    if (S_OK != hr) {
                        LOG_ERROR("Unable to get the font properties after second attempt");
                    }
                }
            }

            SelectObject(dc, oldFont);
        }
    }
    return m_scriptFontProperties;
}