void CMyRibbonBar::addTabAnalyze()
{
	CMFCRibbonCategory* pCategory = AddCategory(_T("Analyze"), IDB_ANALYZE16, IDB_ANALYZE);

	CMFCRibbonPanel* pPanel = pCategory->AddPanel(_T("Selection"), m_PanelImages.ExtractIcon(13));

	pPanel->Add(new CMFCRibbonLabel(_T("Set Focus :")));
	CMFCRibbonComboBox* pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_TEST_SELECT, TRUE, -1,_T("Select Test"),0);
	/*
	pSelectionCB->AddItem(_T("Test1"),0);
		pSelectionCB->AddItem(_T("Test2"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);

	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_ITEM_SELECT, TRUE, -1,_T("Select Item"),7);
	/*
	pSelectionCB->AddItem(_T("ActivityA"),0);
		pSelectionCB->AddItem(_T("Task T1"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);

	pPanel->SetJustifyColumns();

	//
	pPanel = pCategory->AddPanel(_T("Single Activity"), m_PanelImages.ExtractIcon(18));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_TIMELINE, _T("TimeLines"), -1, 0));
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_STAGES, _T("Clustered stages"), -1, 2));
	//pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_TOTALTIME, _T("Total Times"), -1, 0));
		//send to compare.
	
	pPanel->AddSeparator();
	pPanel->Add(new CMFCRibbonLabel(_T("Select Task :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_SINGLEACTIVITY_CB_TASKSEL, TRUE, -1,_T("Task :"),3);
	pPanel->Add(pSelectionCB);

	CMFCRibbonButton* pBtn = new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_STACKED, _T("Stacked"), 0, 1);
	pBtn->SetMenu(IDR_MENU_RIBBON_ACTIVITY1, TRUE);
	pPanel->Add(pBtn);

	pBtn = new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_WITHTASK_TOTAL, _T("Total Times"), 0, 4);
	pBtn->SetMenu(IDR_MENU_RIBBON_ACTIVITY2, TRUE);
	pPanel->Add(pBtn);

	//
	pPanel->AddSeparator();
	pPanel->Add(new CMFCRibbonLabel(_T("Select Worker :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_SINGLEACTIVITY_CB_WORKERSEL, TRUE, -1,_T("Thread :"),1);
/*
	pSelectionCB->AddItem(_T("Worker T0"),0);
	pSelectionCB->AddItem(_T("Thread T1"));
	pSelectionCB->SelectItem(0);*/

	pPanel->Add(pSelectionCB);
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEACTIVITY_WITHWORKER_TOTALTIME, _T("Time Total"), 0, 5));

	pPanel = pCategory->AddPanel(_T("All Activities"), m_PanelImages.ExtractIcon(18));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_ALLACTIVITIES_TOTAL, _T("Total time"), 0, 3));


	pPanel = pCategory->AddPanel(_T("Single Task"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLETASK_RUNSHISTORY, _T("Runs History"), 0, 6));
	//pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLETASK_TOTAL, _T("Total Time"), 0, 0));
		//send to compare.

	pPanel = pCategory->AddPanel(_T("All Tasks"), m_PanelImages.ExtractIcon(19));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_ALLTASKS_TOTAL, _T("Total Time"), 0, 10));
			//add average time ?



	pPanel = pCategory->AddPanel(_T("Worker"), m_PanelImages.ExtractIcon(17));

	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEWORKER_RUNPAUSE, _T("Run|Pause Time"), 0, 12));
	pPanel->AddSeparator();

	pPanel->Add(new CMFCRibbonLabel(_T("Select Task :")));
	pSelectionCB = new CMFCRibbonComboBox(WM_ANALYSIS_SINGLEWORKER_CB_SELTASK, TRUE, -1,_T("Task :"),3);
	/*
	pSelectionCB->AddItem(_T("Task T0"),0);
		pSelectionCB->AddItem(_T("Task T1"));
		pSelectionCB->SelectItem(0);*/
	
	pPanel->Add(pSelectionCB);
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEWORKER_WITHTASK_MULTIPLESTACKED, _T("Multiple Stacked"), 0, 13));
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_SINGLEWORKER_WITHTASK_TIMETOTAL, _T("Time Total"), 0, 14));

	pPanel = pCategory->AddPanel(_T("All Workers"), m_PanelImages.ExtractIcon(27));
	pPanel->Add(new CMFCRibbonButton(WM_ANALYSIS_ALLWORKERS_TOTAL, _T("Total Times"), 0, 11));


	/*
pPanel = pCategory->AddPanel(_T("Tasks and activity"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Pie"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Pie"), 0, 0));

	pPanel = pCategory->AddPanel(_T("Tasks and thread"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Task Pie"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Stacked"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("Tasks Pie"), 0, 0));

	pPanel = pCategory->AddPanel(_T("Threads and activity"), m_PanelImages.ExtractIcon(27));

	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("All Threads Column"), 0, 0));
	pPanel->Add(new CMFCRibbonButton(ID_EDIT_PASTE, _T("all Threads Vs Activity Time two columns"), 0, 0));
*/


}