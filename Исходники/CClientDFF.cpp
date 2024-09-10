bool CClientDFF::LoadDFF(const SString& strFile, bool bIsRawData)
{
    // Should only be called once, directly after construction
    m_bIsRawData = bIsRawData;
    if (!m_bIsRawData)            // If we have actual file
    {
        assert(m_strDffFilename.empty());

        m_strDffFilename = strFile;
        if (m_strDffFilename.empty())
            return false;

        if (!FileExists(m_strDffFilename))
            return false;

        if (!g_pCore->GetNetwork()->CheckFile("dff", m_strDffFilename))
            return false;
    }
    else
    {
        m_RawDataBuffer = CBuffer(strFile, strFile.length());
        if (!g_pCore->GetNetwork()->CheckFile("dff", "", m_RawDataBuffer.GetData(), m_RawDataBuffer.GetSize()))
            return false;
    }

    // Do actual load later (in ReplaceModel)
    return true;
}