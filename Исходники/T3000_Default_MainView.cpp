void T3000_Default_MainView::OnEnKillfocusEditFreid()
{
	//strTemp.Format(_T("%d"), (int)product_register_value[608]);
	//m_Edit_Network.SetWindowTextW(strTemp);
	//strTemp.Format(_T("%d"), (int)product_register_value[609]);
	//m_Edit_NodeID.SetWindowTextW(strTemp);
	CString strTemp;
	m_Edit_FrequenceID.GetWindowTextW(strTemp);
	  long Freq = _wtol(strTemp);
	/*long long Freq = ((long long)product_register_value[610]) * 65536 + ((long long)product_register_value[611]);
	*/
	unsigned short FreArray[2];
	  FreArray[0] = Freq / 65536;
	  FreArray[1] = Freq % 65536;
	  Write_Multi_org_short(g_tstat_id, FreArray, 610, 2, 5);
	  
// 	strTemp.Format(_T("%ld"), Freq);
// 	m_Edit_FrequenceID.SetWindowTextW(strTemp);
}