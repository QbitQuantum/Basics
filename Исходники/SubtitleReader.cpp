CSubtitleText::CSubtitleText(wchar_t *szFile)
{
    m_hFile =  CreateFile(szFile,
                          GENERIC_READ,
                          FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);
    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        m_hFile = NULL;
        return ;
    }

    LARGE_INTEGER liSize;
    GetFileSizeEx(m_hFile, &liSize);

    if (liSize.QuadPart < 16) return ;
    if (liSize.QuadPart > MAX_SUBTITILE_FILE_SIZE) return ;

    int32_t fSize = liSize.LowPart;
    m_Buffer = (uint8_t *)MemoryAlloc(fSize + 8);
    DWORD NumberOfBytesRead = 0;
    ReadFile(m_hFile, m_Buffer, fSize, &NumberOfBytesRead, NULL);
    if (NumberOfBytesRead != fSize) return ;
    ZeroMemory(m_Buffer + fSize, 8);
    SAFE_CLOSE(m_hFile);

    if ((m_Buffer[0] == 0xFF) && (m_Buffer[1] == 0xFE))
    {
        m_Scrpits = (wchar_t *)MemoryAlloc(fSize + 8);
        wchar_t *s = (wchar_t *)&m_Buffer[2];
        while (*s)
        {
            if (*s != L'\r')
            {
                m_Scrpits[m_cCharacter] = *s;
                m_cCharacter ++;
            }
            s++;
        }
        ZeroMemory(&m_Scrpits[m_cCharacter], 8);
    }
    else if ((m_Buffer[0] == 0xEF) && (m_Buffer[1] == 0xBB) && (m_Buffer[2] == 0xBF))
    {
        int32_t len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_Buffer + 3, fSize - 3, NULL, 0);
        if (len == 0) return ;
        m_Scrpits = (wchar_t *)MemoryAlloc(len * 2 + 8);
        m_cCharacter = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)m_Buffer + 3, fSize - 3, m_Scrpits, len * 2 + 2);
        if (m_cCharacter == 0) return ;
        ZeroMemory(&m_Scrpits[m_cCharacter], 8);
        wchar_t *p1 = m_Scrpits;
        wchar_t *p2 = m_Scrpits;
        while(*p2)
        {
            if (*p2 != '\r')*p1++ = *p2;
            p2 ++;
        }
        ZeroMemory(p2, 8);
    }
    else
    {
        INT unicode = IS_TEXT_UNICODE_UNICODE_MASK;
        INT unicodeReverse = IS_TEXT_UNICODE_REVERSE_MASK;
        INT notAscii = IS_TEXT_UNICODE_NOT_ASCII_MASK;
        if (((fSize & 1) == 0) && IsTextUnicode(m_Buffer, fSize, &unicode))
        {
            m_Scrpits = (wchar_t *)MemoryAlloc(fSize + 8);
            wchar_t *s = (wchar_t *)m_Buffer;
            while (*s)
            {
                if (*s != L'\r')
                {
                    m_Scrpits[m_cCharacter] = *s;
                    m_cCharacter ++;
                }
                s++;
            }
            ZeroMemory(&m_Scrpits[m_cCharacter], 8);
        }
        else if (((fSize & 1) == 0) && IsTextUnicode(m_Buffer, fSize, &unicodeReverse))
        {
            m_Scrpits = (wchar_t *)MemoryAlloc(fSize + 8);
            uint8_t *s = m_Buffer;
            while (*((uint16_t *)s))
            {
                wchar_t ch = (uint16_t)s[0] + ((uint16_t)s[1] << 8);
                if (ch != L'\r')
                {
                    m_Scrpits[m_cCharacter] = ch;
                    m_cCharacter ++;
                }
                s += 2;
            }
            ZeroMemory(&m_Scrpits[m_cCharacter], 8);
        }
        else if (IsTextUnicode(m_Buffer, fSize, &notAscii))
        {
            //
        }
        else
        {
            int32_t len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_Buffer, fSize - 3, NULL, 0);
            if (len == 0) return ;
            m_Scrpits = (wchar_t *)MemoryAlloc(len * 2 + 8);
            len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_Buffer, fSize - 3, m_Scrpits, len * 2 + 8);
            if (len == 0) return ;
            if (m_cCharacter == 0) return ;
            ZeroMemory(&m_Scrpits[m_cCharacter], 8);
            wchar_t *p1 = m_Scrpits;
            wchar_t *p2 = m_Scrpits;
            while(*p2)
            {
                if (*p2 != '\r')*p1++ = *p2;
                p2 ++;
            }
            ZeroMemory(p2, 8);
        }
    }

    if (m_cCharacter == NULL)
    {
        return ;
    }
}