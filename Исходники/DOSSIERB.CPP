BOOL Dossier::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);
	title->SetString(GetTargName(uid));

	CRButton*	authbut = GETDLGITEM(IDC_AUTHORISE);
	if (Node_Data.GotBadWeatherPeriod())
		authbut->ShowWindow(SW_HIDE);
	else
	  	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			authbut->SetString(RESSTRING(AUTHORISE));
		else
		{
			authbut->SetString(RESSTRING(PATROL));
			authbut->SetHintString(RESSTRING(HIDC_PATROL));
		}


	authbut = GETDLGITEM(IDC_PHOTO);
	if (Node_Data.GotBadWeatherPeriod())
		authbut->ShowWindow(SW_HIDE);
	else
		if (Node_Data[uid]==Target::TSS_TargetConvoy || Node_Data[uid]==NULL || Node_Data[uid].truetargtype==Target::TT_GERMAN)
			authbut->ShowWindow(SW_HIDE);
		else
		  	if (ReconnRequired())
			{
				authbut->SetString(RESSTRING(RECONN));
				authbut->SetHintString(RESSTRING(HIDC_RECONN));
			}
			else
				authbut->SetString(RESSTRING(PHOTO));
	if (LUF_FighterLF2BAND==Persons2::GetBandFromUID(uid))
	{
	 	authbut = GETDLGITEM(IDC_AUTHORISE);
		authbut->ShowWindow(SW_HIDE);

		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		{
// we now want to display a button for fighters and/or bombers if there are any
// at this LW AF

			int i=0;
			SLong fighters=-1;
			SLong bombers=-1;

			while (Node_Data.gruppe[i].squadron != SQ_ZERO)
			{
				if (Node_Data.gruppe[i].homeairfield == uid)
				{
					if (Node_Data.gruppe[i].AcType()<PT_LW_BOMBERS)
						fighters=i;
					else
						bombers=i;
				}
				i++;
			}

	// Photo button becomes fighters

			if (fighters!=-1)
			{
		 		authbut = GETDLGITEM(IDC_PHOTO);
				authbut->SetString(RESSTRING(FIGHTERS));
				authbut->SetHintString(Node_Data.gruppe[fighters].ShortName());
				authbut->ShowWindow(SW_SHOW);
			}

	// Authorise button becomes bombers

			if (bombers!=-1)
			{
		 		authbut = GETDLGITEM(IDC_AUTHORISE);
				authbut->SetString(RESSTRING(BOMBERS));
				authbut->SetHintString(Node_Data.gruppe[bombers].ShortName());
				authbut->ShowWindow(SW_SHOW);
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}