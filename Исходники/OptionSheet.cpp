void COptionSheet::OnBack()
{
	LRESULT result;
	
	// Make sure there is a current item it has a page
	ASSERT(NULL != m_CurrentPage);

	// Make sure the Next button is enabled
	CWnd *wnd = GetDlgItem(ID_WIZBACK);
	if(NULL == wnd) {
		return;
	}

	if(FALSE == wnd->IsWindowEnabled()) {
		return;
	}

	// Check to see if we can move to the next page
	result = GetPage(m_PageIndex)->OnWizardNext();

	switch(result) {
	case -1:
		break;
	case 0:
		SetActivePage(--m_PageIndex);
		break;
	default:
		if(result > 0) {
			SetActivePage(result);
		}
		break;
	}

	return;
}