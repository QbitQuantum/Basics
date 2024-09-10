void CBrushEntityDialog::OnEntities() 
{
	int Cur;

	// Entity button was clicked
	// Get current entity type from combo box and create one...
	Cur = m_EntityCombo.GetCurSel ();
	if (Cur != LB_ERR)
	{
		char EntityName[_MAX_PATH];
		CWnd *LastView;

		m_EntityCombo.GetLBText (Cur, EntityName);
		/*
		  We create a "light" entity as the template entity.
		  In future, we'll have a "template" entity.
		*/
		m_pFusionDoc->CreateEntity ("light");//EntityName);
		LastView = m_pParentCtrl->LastView;
		if ((LastView != NULL) && ::IsWindow (LastView->m_hWnd))
		{
			LastView->SetFocus ();
		}
	}
}