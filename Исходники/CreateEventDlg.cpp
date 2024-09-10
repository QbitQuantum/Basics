void CCreateEventDlg::OnInitDialog()
{
    RECT r = { 43, 24, 43+211, 24+12 };
    MapDialogRect(m_hwnd, &r);
    m_pTaskCombo->Create(m_hwnd, r, WS_VISIBLE | WS_CHILD, WS_EX_CLIENTEDGE);

    StringBuffer sbFormat(2048);
    LoadString(resInstance, IDS_EVENT_TIME_FORMAT, sbFormat, 2047);
    HWND hwnd = GetDlgItem(m_hwnd, IDC_CREATE_EVENT_TIME);
    SendMessage(hwnd, DTM_SETFORMAT, 0, reinterpret_cast<LPARAM>(sbFormat.operator TCHAR *()));
    m_picker = TimePicker::CreateTimePicker(hwnd);

    SYSTEMTIME st;
    GetLocalTime(&st);
    if(st.wMinute % 15)
    {
        st.wMinute = ((st.wMinute / 15) + 1) * 15;
        if(st.wMinute > 45)
        {
            st.wMinute = 0;
            st.wHour += 1;
        }
    }
    SendMessage(hwnd, DTM_SETSYSTEMTIME, GDT_VALID, reinterpret_cast<LPARAM>(&st));

    hwnd = GetDlgItem(m_hwnd, IDC_CREATE_EVENT_EDIT_DURATION_DAYS);
    m_pEstDuration = new EstDurationEdit(hwnd, false, true);

//	hwnd = GetDlgItem(m_hwnd, IDC_CREATE_EVENT_EDIT_DURATION_HOURS);
//	SetWindowText(hwnd, _T("1"));
}