SCRIPT_FONTPROPERTIES* Font::scriptFontProperties() const
{
    if (!m_scriptFontProperties) {
        m_scriptFontProperties = new SCRIPT_FONTPROPERTIES;
        memset(m_scriptFontProperties, 0, sizeof(SCRIPT_FONTPROPERTIES));
        m_scriptFontProperties->cBytes = sizeof(SCRIPT_FONTPROPERTIES);
        HRESULT result = ScriptGetFontProperties(0, scriptCache(), m_scriptFontProperties);
        if (result == E_PENDING) {
            HWndDC dc(0);
            SaveDC(dc);
            SelectObject(dc, m_platformData.hfont());
            ScriptGetFontProperties(dc, scriptCache(), m_scriptFontProperties);
            RestoreDC(dc, -1);
        }
    }
    return m_scriptFontProperties;
}