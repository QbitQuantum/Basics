void CClusterSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_RadioCluMethod == 0) 
	{
		//如果选择DBSCAN
		if(m_szeps.IsEmpty())   //扫描半径
		{
			MessageBox(L"扫描半径不能为空",L"聚类设置",MB_ICONERROR);
			return;
		}
		m_eps = _wtof(m_szeps);
		if(m_eps == 0)   //扫描半径
		{
			MessageBox(L"请输入合法的扫描半径",L"聚类设置",MB_ICONERROR);
			return;
		}

		if(m_szMinpts.IsEmpty())   //扫描半径
		{
			MessageBox(L"最小点数不能为空",L"聚类设置",MB_ICONERROR);
			return;
		}
		m_Minpts = _wtof(m_szMinpts);
		if(m_Minpts == 0)   //扫描半径
		{
			MessageBox(L"请输入合法的最小点数",L"聚类设置",MB_ICONERROR);
			return;
		}
	}
	else
	{		
		if(m_szClusterNum.IsEmpty())   //扫描半径
		{
			MessageBox(L"聚类类别数不能为空",L"聚类设置",MB_ICONERROR);
			return;
		}
		m_ClusterNum = _wtof(m_szClusterNum);
		if(m_ClusterNum == 0)   //扫描半径
		{
			MessageBox(L"请输入合法的聚类类别数",L"聚类设置",MB_ICONERROR);
			return;
		}
	}
	CDialogEx::OnOK();
}