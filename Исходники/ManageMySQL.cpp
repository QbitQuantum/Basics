void CManageMySQL::OnBnClickedGetdata()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 13;i >= 0;i--)
	{
		GetDlgItem(IDC_BUTTON1 + i)->SetWindowTextA(_T(""));
		GetDlgItem(IDC_BUTTON1 + i)->ShowWindow(SW_HIDE);
	}//隐藏Button


	mysql_set_character_set(&my_connection, "gbk");
	int res;
	//mysql_query(&my_connection, "create database Exam");
	mysql_query(&my_connection, "use student");
	//res = mysql_query(&my_connection, "SELECT * FROM `student` where  (`ID`='1')");
	//char query[200] = { "SELECT * FROM `message` where  (`ID`= 1 )" };
	char query[200] = { "SELECT * FROM `index` LIMIT 0, 1000" };

	res = mysql_query(&my_connection, query);
	MYSQL_RES *result = mysql_store_result(&my_connection);
	char** sql_row = mysql_fetch_row(result);
	DataGuide = 0;
	for (GradeCount = 0;sql_row!=NULL; GradeCount++)
	{
		//int n = m_listcontrol.InsertItem(i, temp);
		//m_listcontrol.SetItemData(n, i);
		


		CString str;
		str.Format(_T("%s"), sql_row[0]);
		CWnd* DlgHwnd = GetDlgItem(IDC_BUTTON1 + GradeCount);
		DlgHwnd->SetWindowText(str);
		DlgHwnd->ShowWindow(SW_SHOW);
		
		/*m_listcontrol.SetItemText(n, 0, str);
		str.Format(_T("%s"), sql_row[1]);
		m_listcontrol.SetItemText(n, 1, str);
		str.Format(_T("%s"), sql_row[2]);
		m_listcontrol.SetItemText(n, 2, str);
		str.Format(_T("%s"), sql_row[3]);
		m_listcontrol.SetItemText(n, 3, str);
		str.Format(_T("%s"), sql_row[4]);
		m_listcontrol.SetItemText(n, 4, str);
		str.Format(_T("%s"), sql_row[5]);
		m_listcontrol.SetItemText(n, 5, str);
		str.Format(_T("%s"), sql_row[6]);
		m_listcontrol.SetItemText(n, 6, str);*/


		sql_row = mysql_fetch_row(result);
		//free(result);
	}
	CWnd* DlgHwnd = GetDlgItem(IDC_BUTTON1 + GradeCount);
	DlgHwnd->SetWindowText(_T("+"));
	DlgHwnd->ShowWindow(SW_SHOW);
	


}