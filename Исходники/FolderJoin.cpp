void CFolderJoin::Escape()
{
	if (m_pPassEdit && GetCapture() == m_pPassEdit)
	{
        SetCapture(LTNULL);
		m_szPassword[0] = LTNULL;
		RemoveFixedControl(m_pPassEdit);
		RemoveFixedControl(m_pPassLabel);
		RemoveFixedControl(m_pPassBack);
		m_bAskingForPassword = FALSE;
		ForceMouseUpdate();
	}
	else
		CBaseFolder::Escape();

}