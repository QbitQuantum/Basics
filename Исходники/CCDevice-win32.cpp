    int drawText(const char * pszText, SIZE& tSize, Device::TextAlign eAlign)
    {
        int nRet = 0;
        wchar_t * pwszBuffer = nullptr;
        wchar_t* fixedText = nullptr;
        do
        {
            CC_BREAK_IF(! pszText);

            DWORD dwFmt = DT_WORDBREAK;
            DWORD dwHoriFlag = (int)eAlign & 0x0f;
            DWORD dwVertFlag = ((int)eAlign & 0xf0) >> 4;

            switch (dwHoriFlag)
            {
            case 1: // left
                dwFmt |= DT_LEFT;
                break;
            case 2: // right
                dwFmt |= DT_RIGHT;
                break;
            case 3: // center
                dwFmt |= DT_CENTER;
                break;
            }

            int nLen = strlen(pszText);
            // utf-8 to utf-16
            int nBufLen  = nLen + 1;
            pwszBuffer = new wchar_t[nBufLen];
            CC_BREAK_IF(! pwszBuffer);

            memset(pwszBuffer, 0, sizeof(wchar_t)*nBufLen);
            nLen = MultiByteToWideChar(CP_UTF8, 0, pszText, nLen, pwszBuffer, nBufLen);

            if (strchr(pszText, '&'))
            {
                fixedText = new wchar_t[nLen * 2 + 1];
                int fixedIndex = 0;
                for (int index = 0; index < nLen; ++index)
                {
                    if (pwszBuffer[index] == '&')
                    {
                        fixedText[fixedIndex] = '&';
                        fixedText[fixedIndex + 1] = '&';
                        fixedIndex += 2;
                    }
                    else
                    {
                        fixedText[fixedIndex] = pwszBuffer[index];
                        fixedIndex += 1;
                    }
                }
                fixedText[fixedIndex] = '\0';
                nLen = fixedIndex;
            }

            SIZE newSize;
            if (fixedText)
            {
                newSize = sizeWithText(fixedText, nLen, dwFmt, tSize.cx);
            }
            else
            {
                newSize = sizeWithText(pwszBuffer, nLen, dwFmt, tSize.cx);
            }

            RECT rcText = {0};
            // if content width is 0, use text size as content size
            if (tSize.cx <= 0)
            {
                tSize = newSize;
                rcText.right  = newSize.cx;
                rcText.bottom = newSize.cy;
            }
            else
            {

                LONG offsetX = 0;
                LONG offsetY = 0;
                rcText.right = newSize.cx; // store the text width to rectangle

                // calculate text horizontal offset
                if (1 != dwHoriFlag          // and text isn't align to left
                    && newSize.cx < tSize.cx)   // and text's width less then content width,
                {                               // then need adjust offset of X.
                    offsetX = (2 == dwHoriFlag) ? tSize.cx - newSize.cx     // align to right
                        : (tSize.cx - newSize.cx) / 2;                      // align to center
                }

                // if content height is 0, use text height as content height
                // else if content height less than text height, use content height to draw text
                if (tSize.cy <= 0)
                {
                    tSize.cy = newSize.cy;
                    dwFmt   |= DT_NOCLIP;
                    rcText.bottom = newSize.cy; // store the text height to rectangle
                }
                else if (tSize.cy < newSize.cy)
                {
                    // content height larger than text height need, clip text to rect
                    rcText.bottom = tSize.cy;
                }
                else
                {
                    rcText.bottom = newSize.cy; // store the text height to rectangle

                    // content larger than text, need adjust vertical position
                    dwFmt |= DT_NOCLIP;

                    // calculate text vertical offset
                    offsetY = (2 == dwVertFlag) ? tSize.cy - newSize.cy     // align to bottom
                        : (3 == dwVertFlag) ? (tSize.cy - newSize.cy) / 2   // align to middle
                        : 0;                                                // align to top
                }

                if (offsetX || offsetY)
                {
                    OffsetRect(&rcText, offsetX, offsetY);
                }
            }

            CC_BREAK_IF(! prepareBitmap(tSize.cx, tSize.cy));

            // draw text
            HGDIOBJ hOldFont = SelectObject(_DC, _font);
            HGDIOBJ hOldBmp  = SelectObject(_DC, _bmp);

            SetBkMode(_DC, TRANSPARENT);
            SetTextColor(_DC, RGB(255, 255, 255)); // white color

            // draw text
            if (fixedText)
            {
                nRet = DrawTextW(_DC, fixedText, nLen, &rcText, dwFmt);
            }
            else
            {
                nRet = DrawTextW(_DC, pwszBuffer, nLen, &rcText, dwFmt);
            }

            //DrawTextA(_DC, pszText, nLen, &rcText, dwFmt);

            SelectObject(_DC, hOldBmp);
            SelectObject(_DC, hOldFont);
        } while (0);
        CC_SAFE_DELETE_ARRAY(pwszBuffer);
        delete[] fixedText;

        return nRet;
    }