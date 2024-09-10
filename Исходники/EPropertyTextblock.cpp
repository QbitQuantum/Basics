bool EPropertyTextblock::OnPropApply()
{
	bool bChangeOK = false;

	if( m_pPropertyEditWindow == NULL )
	{
	}
	else
	{
		CString s = m_pPropertyEditWindow->GetEditText();

		int nNumRemoved = s.Remove(13);	//remove cariage return
		
		bChangeOK = m_pHost->PropertyChanging( m_pProperty , &s );

		if( bChangeOK )
		{
			*((CString*)m_pProperty) = s;
		}

		CloseEditWindow();
	}

	return bChangeOK;
}