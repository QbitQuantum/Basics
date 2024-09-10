// invoked by menu
BOOL CWOrthoChange::doEditDialog(CListCtrl& clc, BOOL bIsNew)
{
	clc.LockWindowUpdate();	//don't want to show the remove

	// 1) remove ourselves from the list control
	int iRow = getRow(clc);
	if(iRow >= 0)	// will be -1 if we were just created
		removeFromListCtrl(clc);

	// 2) do the dialog

	CDlgEditOrthoChange dlg(m_pOwningList->getTextDisplayInfo());
	// Load in all our settings
	dlg.m_bEnabled = m_bEnabled;
/*	if(!m_environments.GetSize())	// make a blank one if we need to
	{
		m_environments.Add(new CStringEnvironment( sEmpty,
												sEmpty,
												m_iColumnForEnv,
												this,
												TRUE, m_iColumnForEnvComment));
	}
*/
	//	dlg.m_sEnvironment = m_environments[0]->m_sEnv;
//	dlg.m_sEnvironComment = m_environments[0]->m_sComments;
	dlg.setRule(this);

	dlg.m_sComments = m_lcComments;
	dlg.m_sFrom = m_sFrom;
	dlg.m_sTo = m_sTo;

	// put up the dialog
	BOOL bDlgOk = dlg.DoModal();
	if(IDOK == bDlgOk)
	{

		// Reload all our settings if the user clicked 'ok'
		m_bEnabled = dlg.m_bEnabled;
		m_lcComments = dlg.m_sComments;
		m_sFrom = dlg.m_sFrom;
		m_sTo = dlg.m_sTo;
/*		if(dlg.m_sEnvironment.GetLength())
		{	m_environments[0]->m_sEnv = dlg.m_sEnvironment;
			m_environments[0]->m_sComments = dlg.m_sEnvironComment;
		}
		else	// the first env can be deleted by clearing that box
			m_environments.RemoveAt(0);
*/
	}

	// 3) add ourselves back in
	if(iRow >= 0)
		addYourRowsToListCtrl(clc, iRow);

	clc.UnlockWindowUpdate();	//now allow it to update


	return (IDOK == bDlgOk);
}