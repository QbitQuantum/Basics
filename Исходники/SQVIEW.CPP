BOOL CQuickView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRStatic*   s=GETDLGITEM(IDC_CURRMISS);
	s->SetString(RESLIST(QUICK_1, CSQuick1::currquickmiss));


		targtype=0,targentry=0;
	for (int t=0;t<4;t++)
		for (int e=0;e<4;e++)
			if(CSQuick1::quickdef.targets[t][e]==CSQuick1::quickdef.target)
				targtype=t,targentry=e;
	s=GETDLGITEM(IDC_TARGTYPE);
	s->SetString(LoadResString(CSQuick1::quickdef.targtypeIDs[targtype]));

	s=GETDLGITEM(IDC_TARGNAME);
	s->SetString(GetTargName(CSQuick1::quickdef.targets[targtype][targentry]));

	s=GETDLGITEM(IDC_WEATHER);
	s->SetString(RESLIST(WEATHER_CLEAR, CSQuick1::quickdef.weather));
	s=GETDLGITEM(IDC_CLOUD);
	s->SetString(CSprintf("%i", 5000 + 1000 * CSQuick1::quickdef.cloudbaseK));
	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}