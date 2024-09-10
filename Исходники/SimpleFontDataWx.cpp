void SimpleFontData::platformDestroy()
{
#if OS(WINDOWS)
    if (m_scriptFontProperties) {
        delete m_scriptFontProperties;
        m_scriptFontProperties = 0;
    }

    if (m_scriptCache)
        ScriptFreeCache(&m_scriptCache);
#endif
}