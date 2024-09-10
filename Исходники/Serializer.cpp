Serializer::Serializer(const CString& hex)
{
    size_t bufLen = hex.GetLength() / 2;
    for (size_t i = 0; i < bufLen; ++i)
    {
        DWORD t;
        if (1 != swscanf_s((LPCTSTR)hex + i * 2, L"%02X", &t))
            throw std::runtime_error("invalid buffer");
        m_storage.push_back((BYTE)t);
    }
    m_buf = &m_storage[0];
    m_size = m_storage.size();
}