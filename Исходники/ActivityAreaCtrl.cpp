bool CActivityAreaCtrl::Create()
{
	for(size_t i = 0; i < ActivityBoxesMaxCount;i++)
	{
		if ( wxGetApp().Prefs.nActBoxType[i] >= 0 && m_ActivityBox[i] == NULL )
		{
			m_ActivityBox[i] = new CActivityBox( m_pPanel, MUSIK_ACTIVITYBOX1 + i, wxGetApp().Prefs.nActBoxType[i] );
			pTopSizer->Add( m_ActivityBox[i], 1, wxEXPAND | wxRIGHT, 1 );
		}
	}

	m_pPanel->Layout();
	//	SetSize( pTopSizer->GetMinSize() );

	SetParent( NULL, false );
	return true;
}