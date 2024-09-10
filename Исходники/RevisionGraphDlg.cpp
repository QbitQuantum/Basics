void CRevisionGraphDlg::OnViewFilter()
{

/*	CSyncPointer<CAllRevisionGraphOptions>
		options (m_Graph.m_state.GetOptions());

	CRevisionInRange* revisionRange = options->GetOption<CRevisionInRange>();
	svn_revnum_t head = m_Graph.m_state.GetHeadRevision();
	svn_revnum_t lowerLimit = revisionRange->GetLowerLimit();
	svn_revnum_t upperLimit = revisionRange->GetUpperLimit();

	CRemovePathsBySubString* pathFilter = options->GetOption<CRemovePathsBySubString>();
*/
	CRevGraphFilterDlg dlg;

	dlg.m_bCurrentBranch = this->m_Graph.m_bCurrentBranch;
	dlg.SetRevisionRange(m_Graph.m_FromRev, m_Graph.m_ToRev);

	if (dlg.DoModal()==IDOK)
	{

		// user pressed OK to dismiss the dialog, which means
		// we have to accept the new filter settings and apply them

		dlg.GetRevisionRange(m_Graph.m_FromRev, m_Graph.m_ToRev);
		// update menu & toolbar

		this->m_Graph.m_bCurrentBranch = dlg.m_bCurrentBranch;

		CMenu * pMenu = GetMenu();
		int tbstate = m_ToolBar.GetToolBarCtrl().GetState(ID_VIEW_FILTER);
		if (m_Graph.m_bCurrentBranch || !m_Graph.m_FromRev.IsEmpty() || !m_Graph.m_ToRev.IsEmpty())
		{
			if (pMenu != NULL)
				pMenu->CheckMenuItem(ID_VIEW_FILTER, MF_BYCOMMAND | MF_CHECKED);
			m_ToolBar.GetToolBarCtrl().SetState(ID_VIEW_FILTER, tbstate | TBSTATE_CHECKED);
		}
		else
		{
			if (pMenu != NULL)
				pMenu->CheckMenuItem(ID_VIEW_FILTER, MF_BYCOMMAND | MF_UNCHECKED);
			m_ToolBar.GetToolBarCtrl().SetState(ID_VIEW_FILTER, tbstate & (~TBSTATE_CHECKED));
		}

		// re-run query

		StartWorkerThread();

	}

}