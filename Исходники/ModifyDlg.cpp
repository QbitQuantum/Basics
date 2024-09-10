void CModifyDlg::CreateCtrl()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int top = rcClient.top + TOPINCREMENT;
	int Left = rcClient.left + LEFTINCREMENT;
	CRect CTRRECT;

	if (PUBLIC == m_tableType || INCODE == m_tableType){
		for (int i = 0;i < m_vHead.size();i++){
			CStatic *Static = new CStatic;
			CTRRECT = SetCtrlPos(Left,top,88,CTRLHEIGHT);
			Static->Create(m_vHead[i],WS_CHILD|WS_VISIBLE,CTRRECT,this);
			Static->SetFont(GetFont());
			Left += 88 + HINCREMENT;
			CEdit *Edit = new CEdit;
			CTRRECT = SetCtrlPos(Left,top - 3,380,EDITHEIGHT);
			Edit->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL,CTRRECT,this,IDC_MODIFY_EDIT);
			Edit->SetFont(GetFont());
			Edit->SetWindowText(m_vData[i]);
			top += VINCREMENT + CTRLHEIGHT ;
			Left = rcClient.left + LEFTINCREMENT;

			if (i == 0){
				Static->EnableWindow(FALSE);
				Edit->EnableWindow(FALSE);
			}
			if (i == m_vHead.size()-1 && INCODE == m_tableType)
			{
				CStatic *Static1 = new CStatic;
				CTRRECT = SetCtrlPos(Left,top,450,CTRLHEIGHT);
				Static1->Create("调度规则 1:最大空闲时间调度 2:最短会话时间调度 3:最高优先级调度",WS_CHILD|WS_VISIBLE,CTRRECT,this);
				Static1->SetFont(GetFont());
				m_StaticObject.push_back(Static1);
			}
			m_StaticObject.push_back(Static);
			m_EidtObject.push_back(Edit);
		}
	}
	if (TP == m_tableType) SetTPRuleCtrl();
}