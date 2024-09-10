LRESULT CBackEndDialog::OnActivateTask(WPARAM wParam, LPARAM lParam)
{
	//get the text
	char* pszTaskName = (char*)wParam;

	//track the old task
	CTask* pOldTask = m_pCurrTask;

	//run through the list and find the task
	CTask* pCurr = m_pHeadTask;

	while(pCurr)
	{
		if(stricmp(pszTaskName, pCurr->GetName()) == 0)
		{
			m_pCurrTask = pCurr;
			break;
		}
		pCurr = pCurr->GetNextTask();
	}

	//clean up the name now
	delete [] pszTaskName;
	pszTaskName = NULL;

	//see if we didn't find the task
	if(pCurr == NULL)
	{
		return false;
	}

	//set the active task name around the progress bar
	CStatic* pTaskName = (CStatic*)GetDlgItem(IDC_STATIC_TASK_NAME);
	CString sText;
	sText.Format("Task: %s", (m_pCurrTask) ? m_pCurrTask->GetName() : "None");
	((CStatic*)GetDlgItem(IDC_STATIC_TASK_NAME))->SetWindowText(sText);

	//also update the progress bar to reflect the change
	SetTaskProgress((m_pCurrTask) ? m_pCurrTask->GetProgress() : 0.0f);

	//if the user was viewing the previous task, then we want to start viewing the new
	//task, the same goes for if the user isn't viewing any tasks
	CTask* pViewedTask = GetViewedTask();
	if((pOldTask == pViewedTask) || (pViewedTask == NULL))
	{
		//find this new task
		for(uint32 nCurrTask = 0; nCurrTask < (uint32)GetTaskList()->GetCount(); nCurrTask++)
		{
			if((CTask*)GetTaskList()->GetItemData(nCurrTask) == m_pCurrTask)
			{
				//this is a match, select it
				GetTaskList()->SetCurSel(nCurrTask);
				ResetMessageList();
				break;
			}
		}
	}

	//save this task as our current subtask
	m_sSubTaskName = (m_pCurrTask) ? m_pCurrTask->GetName() : "";

	//update the title bar
	UpdateTitleNonIconic();	
	
	
	return 0;
}