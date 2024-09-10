void CGoToDlg::OnBnClickedOk2()
{
    UpdateData();

    AfxGetApp()->WriteProfileInt(IDS_R_SETTINGS, IDS_RS_GOTO_LAST_USED, TYPE_FRAME);

    unsigned int frame;
    float fps;
    wchar_t c1[2]; // delimiter character
    wchar_t c2[2]; // unnecessary character

    int result = swscanf_s(m_framestr, L"%u%1s%f%1s", &frame, &c1, _countof(c1), &fps, &c2, _countof(c2));

    if (result == 1) {
        m_time = (REFERENCE_TIME)ceil(10000000.0*frame/m_fps);
        OnOK();
    } else if (result == 3 && c1[0] == L',') {
        m_time = (REFERENCE_TIME)ceil(10000000.0*frame/fps);
        OnOK();
    } else if (result == 0 || c1[0] != L',') {
        AfxMessageBox(ResStr(IDS_GOTO_ERROR_PARSING_TEXT), MB_ICONEXCLAMATION | MB_OK);
    } else {
        AfxMessageBox(ResStr(IDS_GOTO_ERROR_PARSING_FPS), MB_ICONEXCLAMATION | MB_OK);
    }
}