void CIwManagersPropertyPage::UpdateButtons()
{
	bool bIsNextButtonEnabled = false;
	int i = 0;
	for (i = 0; i <= sizeof(g_arrIwManagerControls)/sizeof(TIwManagerControls) - 1; i++) {
		const TIwManagerControls& tIwManagerControls = g_arrIwManagerControls[i];
		CButton* pctlManager = (CButton*)GetDlgItem(tIwManagerControls.nMgrsPageMgrId);
		ASSERT(pctlManager != 0);

		if (pctlManager->GetCheck() == BST_CHECKED)
			bIsNextButtonEnabled = true;
	}

	CPropertySheet* parent = (CPropertySheet*)GetParent();
	ASSERT(parent != 0);

	CWnd* pwndNextBut = parent->GetDlgItem(ID_WIZNEXT);
	ASSERT(pwndNextBut != 0);

	pwndNextBut->EnableWindow(bIsNextButtonEnabled);
}