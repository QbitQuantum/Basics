void CRMessageBox::OnPaint()
{
    if (!IsWindowVisible() || IsIconic())
    {
        CDialog::OnPaint();
        return;
    }

    // 绘制窗口
    CRDialog::OnPaint();

    // 显示图标
    HICON hIcon;
    CRect rcIcon;
    POINT point;

    m_stcIcon.GetWindowRect(&rcIcon);
    ScreenToClient(&rcIcon);
    point.x = rcIcon.left;
    point.y = rcIcon.top;

    // 根据消息框类型加载不同的图标
    switch (m_iType & 0xF0)
    {
    case MB_ICONHAND: // MB_ICONERROR/MB_ICONSTOP
        hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_HAND));
        break;
    case MB_ICONQUESTION:
        hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_QUESTION));
        break;
    case MB_ICONEXCLAMATION: // MB_ICONWARNING
        hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_WARNING));
        break;
    case MB_ICONINFORMATION: // MB_ICONASTERISK
        hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_INFORMATION));
        break;
    case MB_USERICON:
    default:
        hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_INFORMATION));
        break;
    }

    // 画图标
    CDC *pDC = GetDC();
    pDC->DrawIcon(point, hIcon);
    ReleaseDC(pDC);
}