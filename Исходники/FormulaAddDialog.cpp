BOOL CFormulaAddDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

    uiutils::setdlgsize(this, &m_ButtonCancel, &m_ButtonOK);

	queryMaterials();
	
	int mCount = this->materialCount;
	// TODO: Add extra initialization here
	int comboboxID = 1000;
	
	int comboLeft = 50;
	int comboTop = 100;
	int comboWidth =170;
	int comboBottom = 330;
	
	int editHeigh = 24;
	int editWidth = 100;
	int editID = 2000;
	int editLeft = 250;
	int editTop = 100;
	
	for(int i = 0; i < mCount ; ++i)
	{
		CString mTitle, pTitle;
		mTitle = (i >= 10) ? "材料名" : "";
		pTitle = (i >= 10) ? "百分比" : "";

		//m_MaterialSecond.SetWindowText(mTitle);
		//m_PercentageSecond.SetWindowText(pTitle);

		if (i == 10)
		{
			comboLeft = 400;
			editLeft = 620;
			comboTop = 100;
			editTop = 100;
		}
		
		CComboBox* testCombox = new CComboBox;
		testCombox->Create(CBS_DROPDOWNLIST|WS_VISIBLE |WS_VSCROLL ,
			CRect(comboLeft,comboTop,comboLeft + comboWidth,comboBottom),  this, comboboxID++);
		
		for (size_t j = 0; j < materialVector.size(); ++j)
		{
			testCombox->AddString(materialVector[j]);
		}

		testCombox->SetFont(SingletonHelper::getInstance()->defaultFont, TRUE);
		testCombox->SetCurSel(0);
		testCombox->ShowWindow(SW_SHOW);
		comboboxVector.push_back(testCombox);
		
		CEdit* testEdit = new CEdit;
		testEdit->CreateEx(WS_EX_CLIENTEDGE, "Edit", "", WS_CHILD|WS_VISIBLE|ES_LEFT,   
			CRect(editLeft,editTop,editLeft + editWidth,editTop + editHeigh), this, editID);
		testEdit->ShowWindow(SW_SHOW);
		editVector.push_back(testEdit);

		comboTop += 50;
		comboBottom += 50;
		editTop += 50;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}