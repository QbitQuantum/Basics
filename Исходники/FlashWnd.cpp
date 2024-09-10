OLECONTAINER(void)::Draw(HDC hdcDraw, const RECT *rcDraw, BOOL bErase)
{
    HWND hwnd = GetHWND();
    HRESULT hr;
    RECT r;

    IOleObject *lpO = m_lpO;
    IViewObject *lpV = m_lpViewObjectEx ? (IViewObject *)m_lpViewObjectEx : m_lpViewObject;

    if (!m_bTransparent)
    {
        RECT rTotal;
        ::GetClientRect(hwnd, &rTotal);
        if (lpV)
        {
            if (!hdcDraw)
            {
                hdcDraw = ::GetDC(hwnd);
                hr = OleDraw(lpV, DVASPECT_CONTENT, hdcDraw, &rTotal);
                ::ReleaseDC(hwnd, hdcDraw);
            }
            else
            {
                hr = OleDraw(lpV, DVASPECT_CONTENT, hdcDraw, &rTotal);
            }
        }
        return;
    }

    ::GetWindowRect(hwnd, &r);
    if (!m_hdcBack || !EqualRect(&r, &m_rcBounds))
    {
        if (m_hdcBack)
            ::DeleteDC(m_hdcBack);
        if (m_bmpBack)
            ::DeleteObject(m_bmpBack);
        if (m_hdcBackW)
            ::DeleteDC(m_hdcBackW);
        if (m_bmpBackW)
            ::DeleteObject(m_bmpBackW);
        m_rcBounds = r;
        HDC hdc = ::GetDC(hwnd);
        BITMAPINFOHEADER bih = {0};
        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biBitCount = 32;
        bih.biCompression = BI_RGB;
        bih.biPlanes = 1;
        bih.biWidth = r.right - r.left;
        bih.biHeight = -(r.bottom - r.top);
        m_hdcBack = CreateCompatibleDC(hdc);
        m_bmpBack = CreateDIBSection(hdc, (BITMAPINFO *)&bih, DIB_RGB_COLORS, (void **)&m_lpBitsOnly, NULL, 0x0);
        SelectObject(m_hdcBack, m_bmpBack);
        if (m_bFixTransparency)
        {
            m_hdcBackW = CreateCompatibleDC(hdc);
            m_bmpBackW = CreateDIBSection(hdc, (BITMAPINFO *)&bih, DIB_RGB_COLORS, (void **)&m_lpBitsOnlyW, NULL, 0x0);
            SelectObject(m_hdcBackW, m_bmpBackW);
        }
        ::ReleaseDC(hwnd, hdc);
        if (m_iBPP == 0)
            m_iBPP = GetDeviceCaps(m_hdcBack, BITSPIXEL);
    }
    POINT p = {r.left, r.top};
    POINT p2 = {0, 0};
    SIZE sz = {r.right-r.left, r.bottom-r.top};

    if (lpO && lpV)
    {
        RECT rTotal;
        ::GetClientRect(hwnd, &rTotal);
        RECTL rcBounds = {rTotal.left, rTotal.top, rTotal.right, rTotal.bottom};
        BYTE *dst = m_lpBitsOnly, *dstW;
        if (m_iBPP == 32)
        {
            if (!m_bFixTransparency) //if flash player version is other than 8, do usual painting
            {
                memset(m_lpBitsOnly, 0, sz.cx * sz.cy * 4);
                hr = OleDraw(lpV, DVASPECT_TRANSPARENT, m_hdcBack, &rTotal);
            }
            else //if player version is 8, we need to fix flash player 8 control transparency bug
            {
                memset(m_lpBitsOnly, 0, sz.cx * sz.cy * 4);
                memset(m_lpBitsOnlyW, 255, sz.cx * sz.cy * 4);
                hr = OleDraw(lpV, DVASPECT_TRANSPARENT, m_hdcBack, &rTotal);
                hr = OleDraw(lpV, DVASPECT_TRANSPARENT, m_hdcBackW, &rTotal);
                dst = m_lpBitsOnly;
                dstW = m_lpBitsOnlyW;
                BYTE r, g, b, a, rw, gw, bw, aw, alpha_r, alpha_g, alpha_b, alpha;
                for (int y = 0; y < sz.cy; y++)
                {
                    for (int x = 0; x < sz.cx; x++)
                    {
                        //the idea is that we draw the same data onto black and white DC's
                        //and then calculate per pixel alpha based on difference, produced by alpha blending
                        r = *dst++;
                        g = *dst++;
                        b = *dst++;
                        a = *dst++;
                        rw = *dstW++;
                        gw = *dstW++;
                        bw = *dstW++;
                        aw = *dstW++;
                        alpha_r = rw-r;
                        alpha_g = gw-g;
                        alpha_b = bw-b;
                        //division by 3 is for accuracy and can be replaced by
                        //alpha = alpha_g; for example
                        alpha = (alpha_r + alpha_g + alpha_b) / 3;
                        *(dst - 1) = 255 - alpha;
                        //this algorithm should be optimized for MMX to achieve best performance
                    }
                } 
            }
        }
        else //in 8/16/24 bit screen depth UpdateLayeredWindow produces wrong results - we use underlaying DC to paint to
        {
            //HWND hwndParent = ::GetParent(hwnd);
            HDC hdcParent = ::GetWindowDC(hwnd);
            BOOL bRet = BitBlt(m_hdcBack, 0, 0, rTotal.right, rTotal.bottom, hdcParent, 0, 0, SRCCOPY);
            ::ReleaseDC(hwnd, hdcParent);
            hr = OleDraw(lpV, DVASPECT_TRANSPARENT, m_hdcBack, &rTotal);
            dst = m_lpBitsOnly;
        }
    }

    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.AlphaFormat = AC_SRC_ALPHA;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;
    //BitBlt(hdcDraw, 0, 0, r.right-r.left, r.bottom-r.top, m_hdcBack, 0, 0, SRCCOPY);
    BOOL bRet = UpdateLayeredWindow(hwnd, NULL, &p, &sz, m_hdcBack, &p2, 0, &bf, /*m_iBPP == 32 ? ULW_ALPHA : */ULW_OPAQUE);
}