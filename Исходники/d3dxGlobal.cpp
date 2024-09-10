void* CDataBlockStore::Allocate(_In_ uint32_t bufferSize)
{
    void *pRetValue = nullptr;

#if _DEBUG
    m_cAllocations++;
#endif

    if (!m_pFirst)
    {
        m_pFirst = new CDataBlock();
        if (!m_pFirst)
            return nullptr;

        if (m_IsAligned)
        {
            m_pFirst->EnableAlignment();
        }
        m_pLast = m_pFirst;
    }

    if (FAILED(UIntAdd(m_Size, bufferSize, &m_Size)))
        return nullptr;

    pRetValue = m_pLast->Allocate(bufferSize, &m_pLast);
    if (!pRetValue)
        return nullptr;

    return pRetValue;
}