void CMessageDialog::SetBkColor(DWORD dwBackColor)
{
	CControlUI* background = m_pm.FindControl(kWndBackGround);
	if (background != NULL)
	{
		background->SetBkImage(_T(""));
		background->SetBkColor(dwBackColor);
		background->NeedUpdate();
	}

}