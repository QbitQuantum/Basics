    INT32 CNetData::AddString(const CHAR *pszString, INT32 iSize)
    {
        static const INT32 BUFLEN = 4096;
        size_t iLen = 0;
		//去掉libiconv库的依赖，避免iphone可能的移植问题
		/*
        if ((m_iCharsetNet >= 0) || (m_iCharsetHost >= 0))
        {
            if (m_iCharsetNet != m_iCharsetHost)
            {
                static char szBuffer[BUFLEN];
                INT32 iResult = 0;
                iLen = BUFLEN;
                iResult = SDIconvCovert(g_szCharset[m_iCharsetNet], 
                    g_szCharset[m_iCharsetHost], const_cast<char*>(pszString), iSize, szBuffer, iLen);
                if (0 != iResult)
                {
                    return -1;
                }
                if((INT32)(m_iPos + (INT32)sizeof(UINT16) + iLen) > m_iSize)
                {
                    return -1;
                }
	            if(-1 == AddWord((UINT16)iLen))
                {
		            return -1;
                }
                memcpy(m_pBuf + m_iPos, szBuffer, iLen);
	            m_iPos += iLen;
                return m_iPos;
            }
        }
		*/

        iLen = Strnlen(pszString, iSize-1);

        if((INT32)(m_iPos + (INT32)sizeof(UINT16) + iLen) > m_iSize)
	        return -1;

        if(-1 == AddWord((UINT16)iLen))
	        return -1;

        memcpy(m_pBuf + m_iPos, pszString, iLen);
        m_iPos += iLen;

	    return m_iPos;
    }