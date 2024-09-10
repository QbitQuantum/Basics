BOOL CNotifyWindow::Create(char *Subject, char *Subtext, char *Text)
{
    DWORD dwExStyle=WS_EX_TOOLWINDOW | WS_EX_TOPMOST;

    CRect rcPos(0,0,0,0);
    if(!WindowBase::Create(NULL,rcPos,"",WS_POPUP,dwExStyle))
        return FALSE;

    m_Image = new CxImage();
    _LoadIconFromResource(m_Image, "PNG", CXIMAGE_FORMAT_PNG, IDB_NOTIFYWINDOWBACK);


    HDC hdc;
    long h1, h2;

    hdc = ::GetDC(NULL);
    h1 = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    h2 = -MulDiv(9, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ::ReleaseDC(NULL, hdc);
    m_SubjectFont = CreateFont(h1, 0, 0, 0, FW_BOLD, FALSE, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
    m_TextFont = CreateFont(h2, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Tahoma");

    m_Subject = new Buffer();
    m_Subject->Append(Subject);
    m_Text = new Buffer();
    m_Text->Append(Text);
    m_Subtext = new Buffer();
    if (*Subtext)
    {
        m_Subtext->Append("(");
        m_Subtext->Append(Subtext);
        m_Subtext->Append(")");
    }

    APPBARDATA	abd;
    memset(&abd, 0, sizeof(APPBARDATA));
    abd.cbSize = sizeof(APPBARDATA);
    SHAppBarMessage(ABM_GETTASKBARPOS, &abd);

    ::GetWindowRect(GetDesktopWindow(), &m_Rect);
    if (abd.uEdge == ABE_BOTTOM)
        m_Rect.bottom -= (abd.rc.bottom - abd.rc.top);
    if (abd.uEdge == ABE_RIGHT)
        m_Rect.right -= (abd.rc.right - abd.rc.left);

    m_Rect.top = m_Rect.bottom - m_Image->GetHeight();
    m_Rect.left = m_Rect.right - m_Image->GetWidth();

    memcpy(&m_ShowRect, &m_Rect, sizeof(RECT));
    m_ShowRect.top = m_Rect.bottom;
    SetWindowPos(NULL, &m_ShowRect, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    SetTimer(1, 100);
    return TRUE;
}