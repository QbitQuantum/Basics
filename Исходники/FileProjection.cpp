    /*
        Release mapping, if any
    */
    void CFileProjection::Release()
    {
        if(m_hctx != INVALID_HANDLE_VALUE)
        {
            ReleaseActCtx(m_hctx);
            m_hctx = INVALID_HANDLE_VALUE;
        }

        if(m_pData)
        {
            UnmapViewOfFile(m_pData);
            m_pData = nullptr;
        }

        if(m_hMapping && m_hMapping != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_hMapping);
            m_hMapping = NULL;
        }

        if(m_hFile != INVALID_HANDLE_VALUE)
        {
            CloseHandle(m_hFile);
            m_hFile = INVALID_HANDLE_VALUE;
        }
    }