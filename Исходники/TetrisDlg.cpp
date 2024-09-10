void CTetrisDlg::UpdateWindow()
{
    CDC wndMemDC;
    wndMemDC.CreateCompatibleDC(&m_memDC);
    wndMemDC.SelectObject(m_window);
    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;
    bf.AlphaFormat = AC_SRC_ALPHA;
    ::AlphaBlend(m_memDC, 328, 10, 308, 629, wndMemDC, 0, 0, 308, 629, bf);
    wndMemDC.DeleteDC();

    SetFontSize(30);
    CString str;
    DrawText(360, 32, 600, 64, str = "NEXT TETROMINO:", DT_LEFT);
    CDC blockMemDC;
    blockMemDC.CreateCompatibleDC(&m_memDC);
    blockMemDC.SelectObject(m_block);
    BYTE x = (m_nextColor - 1) << 5;
    switch((m_gameParam & 0xE0) >> 5)
    {
    case 1:
        m_memDC.StretchBlt(414, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(446, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(478, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(510, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        break;
    case 2:
        m_memDC.StretchBlt(430, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(494, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(494, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        break;
    case 3:
        m_memDC.StretchBlt(430, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(494, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(430, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        break;
    case 4:
        m_memDC.StretchBlt(446, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(478, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(446, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(478, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        break;
    case 5:
        m_memDC.StretchBlt(462, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(494, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(430, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        break;
    case 6:
        m_memDC.StretchBlt(430, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(494, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        break;
    case 7:
        m_memDC.StretchBlt(430, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 96, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(462, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
        m_memDC.StretchBlt(494, 128, 32, 32, &blockMemDC, x, 0, 32, 32, SRCCOPY);
    }
    blockMemDC.DeleteDC();
    DrawText(360, 192, 600, 224, str = "LEVEL:", DT_LEFT);
    str.Format(_T("%d"), m_level + 1);
    DrawText(360, 192, 600, 224, str, DT_RIGHT);
    DrawText(360, 256, 600, 288, str = "SCORE:", DT_LEFT);
    str.Format(_T("%d"), m_score);
    DrawText(360, 256, 600, 288, str, DT_RIGHT);
    DrawText(360, 320, 600, 352, str = "LINES:", DT_LEFT);
    str.Format(_T("%d"), m_lines);
    DrawText(360, 320, 600, 352, str, DT_RIGHT);
    SetFontSize(m_mouseOver == 0x01 ? 36 : 30);
    DrawText(360, 384, 600, 416, str = "NEW", DT_CENTER);
    if(!(m_gameParam & 0x01) || (m_gameParam & 0x04))
    {
        SetFontSize(30);
        DrawText(400, 448, 560, 480, str = "PAUSE", DT_LEFT, 0xA0A0A0);
        DrawText(400, 448, 560, 480, str = "STOP", DT_RIGHT, 0xA0A0A0);
    }
    else
    {
        SetFontSize(m_mouseOver == 0x02 ? 36 : 30);
        DrawText(400, 448, 560, 480, str = "PAUSE", DT_LEFT, m_gameParam & 0x02 ? 0x0000FF : 0xFFFFFF);
        SetFontSize(m_mouseOver == 0x04 ? 36 : 30);
        DrawText(400, 448, 560, 480, str = "STOP", DT_RIGHT, 0xFFFFFF);
    }
    SetFontSize(m_mouseOver == 0x08 ? 36 : 30);
    SetTextColor(m_memDC, 0xFFFFFF);
    DrawText(360, 512, 600, 544, str = "SOUND", DT_CENTER, m_gameParam & 0x08 ? 0x0000FF : 0xFFFFFF);
    SetFontSize(m_mouseOver == 0x10 ? 36 : 30);
    DrawText(360, 576, 600, 608, str = "EXIT", DT_CENTER);
}