void CFolderSave::Escape()
{
	if (GetCapture())
	{
        m_pEdit->Select(LTFALSE);
		g_pColCtrl->SetString(0, g_hOldName);
		g_pColCtrl->SetString(2, g_hOldTime);
		SetCapture(LTNULL);
		RemoveFixedControl(m_pEdit);
	}
	else
	{
		CBaseFolder::Escape();
	}

}