BOOL CDlgRemVag::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_List.ModifyStyle(LVS_NOCOLUMNHEADER, LVS_REPORT | LVS_SHOWSELALWAYS | WS_VISIBLE | WS_BORDER | WS_CHILD, 0);
    m_List.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_FLATSB  );    

    m_EdCount.ModifyStyle(0, WS_DISABLED);
/*
    m_Check1.EnableWindow(FALSE);
    m_Check2.EnableWindow(FALSE);
    m_Check3.EnableWindow(FALSE);
    m_Check4.EnableWindow(FALSE);
    m_Check5.EnableWindow(FALSE);
*/
    m_Dat1.EnableWindow(FALSE);
    m_Dat2.EnableWindow(FALSE);
    m_Dat3.EnableWindow(FALSE);
    m_Dat4.EnableWindow(FALSE);
    m_Cb.EnableWindow(FALSE);
    m_EditNVag.EnableWindow(FALSE);

    DBW.FillComboWithTRemVag(&m_Cb);

	if( g_iMessageNumber )
	{
		m_ButAddVag.ModifyStyle(WS_VISIBLE, 0);
		m_ButDelVag.ModifyStyle(WS_VISIBLE, 0);
	}

    CButton *b1, *b2;
    b1 = (CButton *)GetDlgItem(IDC_RADIO1);
    b2 = (CButton *)GetDlgItem(IDC_RADIO2);
    b1->SetCheck(1);
    b1->EnableWindow(FALSE);
    b2->EnableWindow(FALSE);
	if( g_iStandAlone ) 
	{
		m_ButVagInRem.ModifyStyle(WS_VISIBLE, 0);
		m_ButNeispVag.ModifyStyle(WS_VISIBLE, 0);
	}

    bGotHeader = false;

    m_Menu = new CMenu;
//    m_Menu->CreatePopupMenu();
    m_Menu->LoadMenu(IDR_MENU_VAG);
//    ASSERT(m_Menu->m_hMenu);    
//    m_Menu->AppendMenu(MF_STRING, 0, "asd");
    SYSTEMTIME st;
    GetLocalTime(&st);
	if( st.wDay > 10 )
	{
		st.wDay-=10;
	} else
	{
		int tttt = 10 - st.wDay;
		st.wMonth--;
		if( st.wMonth == 0 )
		{
			st.wMonth = 12;
			st.wYear--;
		}
		st.wDay = 30 - tttt;
	}
/*
    if( st.wMonth == 1 )
    {
        st.wMonth = 12;
        st.wYear--;
    } else
        st.wMonth--;
*/
	if( st.wDay == 31 || st.wDay == 30 ) 
	{
		st.wDay = 1; 
		st.wMonth++;
		if( st.wMonth > 12 ) {st.wMonth = 1; st.wYear++;}
	}
	if( st.wDay > 28 && st.wMonth == 2 ) st.wDay = 28;
    m_Dat1.SetTime(&st);
    m_Dat2.InitDate();
    m_Check2.SetCheck(1);
    OnCheck2();

    RefreshList();


/*    DWORD nCol = 0;
    SYSTEMTIME st;
    ZeroMemory(&st, sizeof(st));
    char dt[16] = "";
    m_Dat1.GetTime(&st);
    DateToSql(st, dt);
    CString str;
    str.Format("pTov_GetAllRemVans %u, %s", g_iDep, dt);
    DBW.ExecSQL(str);
    DBW.SetListHeader(&m_List);
    DBW.UpdateListByHandle(&m_List, &nCol);
    DBW.CloseCursor();
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}