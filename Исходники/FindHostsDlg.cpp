void CFindHostsDlg::Refresh()
{
    DWORD num_read=0, total=0, size;
    int index;
    SERVER_INFO_100 *pBuf = NULL;
    char tBuf[100], tLocalHost[100];
    DWORD ret_val;

    UpdateData();

    HCURSOR hOldCursor = SetCursor( LoadCursor(NULL, IDC_WAIT) );
    
    if (m_domain == "")
    {
	ret_val = NetServerEnum(
	    NULL, 
	    100,
	    (LPBYTE*)&pBuf,
	    MAX_PREFERRED_LENGTH,
	    &num_read,
	    &total,
	    SV_TYPE_NT, 
	    NULL,
	    0);
    }
    else
    {
	WCHAR wDomain[100];
	mbstowcs(wDomain, m_domain, 100);
	ret_val = NetServerEnum(
	    NULL, 
	    100,
	    (LPBYTE*)&pBuf,
	    MAX_PREFERRED_LENGTH,
	    &num_read,
	    &total,
	    SV_TYPE_NT, 
	    (LMCSTR)wDomain,
	    0);
    }
    
    if (ret_val == NERR_Success)
    {
	size = 100;
	GetComputerName(tLocalHost, &size);
	m_list.DeleteAllItems();
	if (num_read == 0)
	{
	    //m_list.InsertItem(0, tLocalHost, 0);
	    //m_list.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	    InsertHost(tLocalHost);
	    SelectHost(tLocalHost);
	}
	else
	{
	    index = -1;
	    for (unsigned int i=0; i<num_read; i++)
	    {
		wcstombs(tBuf, (WCHAR*)pBuf[i].sv100_name, wcslen((WCHAR*)pBuf[i].sv100_name)+1);
		InsertHost(tBuf);
		/*
		index = m_list.InsertItem(0, tBuf, 0);
		if (stricmp(tBuf, tLocalHost) == 0)
		    index = ret_val;
		else
		    index = -1;
		*/
	    }
	    /*
	    if (index != -1)
	    {
		m_list.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
	    }
	    */
	    SelectHost(tLocalHost);
	}
	NetApiBufferFree(pBuf);
    }
    else
    {
	sprintf(tBuf, "error: %d", ret_val);
	MessageBox(tBuf, "Unable to retrieve network host names");
    }
    
    SetCursor(hOldCursor);
}