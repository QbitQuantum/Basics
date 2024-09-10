// called by CWListView::OnInitialUpdate
void CWList::populateListCtrl(CListCtrl &clc)
{

	clc.LockWindowUpdate();	//don't want to show the remove

	int iNextRow = 0;
	for (int iEntry = 0; iEntry < m_pEntries.GetSize(); iEntry++)
	{
		iNextRow = addItemToListControl(clc, iEntry, iNextRow);
		//iNextRow = m_pEntries[r]->addYourRowsToListCtrl(clc, lvi, iNextRow);
	}


	clc.UnlockWindowUpdate();	//don't want to show the remove

}