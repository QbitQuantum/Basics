    bool setFont(const char * pFontName = NULL, int nSize = 0)
    {
        bool bRet = false;
        do
        {
            std::string fontName = pFontName;
            std::string fontPath;
            HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            LOGFONTA    tNewFont = {0};
            LOGFONTA    tOldFont = {0};
            GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);
            if (fontName.c_str())
            {
                // create font from ttf file
                int nFindttf = fontName.find(".ttf");
                int nFindTTF = fontName.find(".TTF");
                if (nFindttf >= 0 || nFindTTF >= 0)
                {
                    fontPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fontName.c_str());
                    int nFindPos = fontName.rfind("/");
                    fontName = &fontName[nFindPos+1];
                    nFindPos = fontName.rfind(".");
                    fontName = fontName.substr(0,nFindPos);
                }
                else
                {
                    size_t nFindPos = fontName.rfind("/");
                    if (nFindPos != fontName.npos)
                    {
                        if (fontName.length() == nFindPos + 1)
                        {
                            fontName = "";
                        }
                        else
                        {
                            fontName = &fontName[nFindPos+1];
                        }
                    }
                }
                tNewFont.lfCharSet = DEFAULT_CHARSET;
#if defined(__MINGW32__)
                strcpy(tNewFont.lfFaceName, fontName.c_str());
#elif defined(_MSC_VER) && _MSC_VER <= 1200
                strcpy(tNewFont.lfFaceName, fontName.c_str());
#else
                strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
#endif
            }
            if (nSize)
            {
                tNewFont.lfHeight = -nSize;
            }
            GetObjectA(m_hFont,  sizeof(tOldFont), &tOldFont);

            if (tOldFont.lfHeight == tNewFont.lfHeight
                    && 0 == strcmp(tOldFont.lfFaceName, tNewFont.lfFaceName))
            {
                // already has the font
                bRet = true;
                break;
            }

            // delete old font
            if (m_hFont != hDefFont)
            {
                DeleteObject(m_hFont);
                // release old font register
                if (m_curFontPath.size() > 0)
                {
                    wchar_t * pwszBuffer = utf8ToUtf16(m_curFontPath);
                    if (pwszBuffer)
                    {
                        if(RemoveFontResourceW(pwszBuffer))
                        {
                            SendMessage( m_hWnd, WM_FONTCHANGE, 0, 0);
                        }
                        delete [] pwszBuffer;
                        pwszBuffer = NULL;
                    }
                }
                if (fontPath.size() > 0)
                    m_curFontPath = fontPath;
                else
#if defined(_MSC_VER) && _MSC_VER <= 1200
                    m_curFontPath.erase();
#else
                    m_curFontPath.clear();
#endif
                // register temp font
                if (m_curFontPath.size() > 0)
                {
                    wchar_t * pwszBuffer = utf8ToUtf16(m_curFontPath);
                    if (pwszBuffer)
                    {
                        if(AddFontResourceW(pwszBuffer))
                        {
                            SendMessage( m_hWnd, WM_FONTCHANGE, 0, 0);
                        }
                        delete [] pwszBuffer;
                        pwszBuffer = NULL;
                    }
                }
            }
            m_hFont = NULL;

            // disable Cleartype
            tNewFont.lfQuality = ANTIALIASED_QUALITY;

            // create new font
            m_hFont = CreateFontIndirectA(&tNewFont);
            if (! m_hFont)
            {
                // create failed, use default font
                m_hFont = hDefFont;
                break;
            }

            bRet = true;
        } while (0);
        return bRet;
    }