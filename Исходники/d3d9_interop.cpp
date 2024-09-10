    void print_info(LPDIRECT3DSURFACE9 pSurface, int mode, float time, cv::String oclDevName)
    {
        HDC hDC;

        HRESULT r = pSurface->GetDC(&hDC);
        if (FAILED(r))
        {
            return;
        }

        HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FONT);

        HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);

        if (hOldFont)
        {
            TEXTMETRIC tm;
            ::GetTextMetrics(hDC, &tm);

            char buf[256];
            int  y = 0;

            buf[0] = 0;
            sprintf(buf, "mode: %s", m_modeStr[mode].c_str());
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            y += tm.tmHeight;
            buf[0] = 0;
            sprintf(buf, m_demo_processing ? "blur frame" : "copy frame");
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            y += tm.tmHeight;
            buf[0] = 0;
            sprintf(buf, "time: %4.1f msec", time);
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            y += tm.tmHeight;
            buf[0] = 0;
            sprintf(buf, "OpenCL device: %s", oclDevName.c_str());
            ::TextOut(hDC, 0, y, buf, (int)strlen(buf));

            ::SelectObject(hDC, hOldFont);
        }

        r = pSurface->ReleaseDC(hDC);

        return;
    } // print_info()