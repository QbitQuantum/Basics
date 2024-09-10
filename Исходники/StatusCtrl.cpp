void CStatusCtrl::OnOutputcontextClearall()
{
    USES_CONVERSION;

    CString rtfstr = m_RTFHeader;

    rtfstr += "} ";

    char *buffer = new char[rtfstr.GetLength() + 5];
    strcpy(buffer + 4, T2CA(rtfstr));
    *(int *)buffer = 0;

    EDITSTREAM es;
    es.dwCookie = (DWORD)buffer; // Pass a pointer to the CString to the callback function
    es.pfnCallback = RichEditStreamInCallback; // Specify the pointer to the callback function.

    StreamIn(SF_RTF, es); // Perform the streaming
    SetSel(-1, -1);
    LimitText(1000*1000);
    int res = GetLimitText();

    delete [] buffer;

    m_bEmpty = TRUE;
    m_nMoveToBottom = 0;
}