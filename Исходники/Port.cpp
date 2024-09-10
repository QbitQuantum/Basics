BOOL CPort::Open(const char* pszFileName, BOOL fIsSocket)
{
    RIL_LOG_VERBOSE("CPort::Open() - Enter  fIsSocket=[%d]\r\n", fIsSocket);
    BOOL fRet = FALSE;

    if (NULL == pszFileName)
    {
        RIL_LOG_CRITICAL("CPort::Open() - pszFileName is NULL!\r\n");
        return FALSE;
    }

    if (!m_fIsPortOpen)
    {
        if (NULL == m_pFile)
        {
            m_pFile = new CFile();
        }

        if (fIsSocket)
        {
            fRet = OpenSocket(pszFileName);
        }
        else
        {
            fRet = OpenPort(pszFileName);
        }
    }
    else
    {
        RIL_LOG_CRITICAL("CPort::Open() - Port is already open!\r\n");
    }

    RIL_LOG_VERBOSE("CPort::Open() - Exit\r\n");
    return fRet;
}