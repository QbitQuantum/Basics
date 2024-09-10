    ~ProcessorCounter()
    {
        if( m_hQuery )
        {
            PdhCloseQuery( m_hQuery );
            m_hQuery = NULL;
        }

        if( m_szCounterPath )
        {
            delete [] m_szCounterPath;
        }
    }