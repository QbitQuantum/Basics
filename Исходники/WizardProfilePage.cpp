BOOL CWizardProfilePage::OnSetActive()
{
	SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );

	m_sNick = MyProfile.GetNick();

	if ( m_sNick.IsEmpty() )
	{
		TCHAR pBuffer[64];
		DWORD nSize = 64;
		if ( GetUserNameW( pBuffer, &nSize ) ) m_sNick = pBuffer;
	}

	if ( CXMLElement* pVitals = MyProfile.GetXML( _T("vitals") ) )
	{
		CString strGender	= pVitals->GetAttributeValue( _T("gender") );
		CString strAge		= pVitals->GetAttributeValue( _T("age") );

		if ( strGender.CompareNoCase( _T("male") ) == 0 )
		{
			m_nGender = 1;
		}
		else if ( strGender.CompareNoCase( _T("female") ) == 0 )
		{
			m_nGender = 2;
		}

		int nAge = 0;
		_stscanf( strAge, _T("%i"), &nAge );

		for ( int nAgeItem = 0 ; nAgeItem < m_wndAge.GetCount() ; nAgeItem ++ )
		{
			if ( m_wndAge.GetItemData( nAgeItem ) == DWORD( nAge ) )
			{
				m_nAge = nAgeItem;
				break;
			}
		}
	}

	if ( CXMLElement* pLocation = MyProfile.GetXML( _T("location") ) )
	{
		if ( CXMLElement* pPolitical = pLocation->GetElementByName( _T("political") ) )
		{
			m_sLocCountry	= pPolitical->GetAttributeValue( _T("country") );
			m_sLocCity		= pPolitical->GetAttributeValue( _T("city") ) + _T(", ")
							+ pPolitical->GetAttributeValue( _T("state") );
		}
	}

	UpdateData( FALSE );

	OnSelChangeCountry();

	return CWizardPage::OnSetActive();
}