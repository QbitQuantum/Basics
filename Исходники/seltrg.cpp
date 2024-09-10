BOOL SelectTarget::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRCombo* combo;
	CRButton*	but = GETDLGITEM(IDC_RBUTTONRESET);


	combo=GETDLGITEM(IDC_RCOMBOTARGET);
	if  (	(currtab == -1)
		||	(RFullPanelDial::gameside != RFullPanelDial::SIDE_LW)
		)

	{
		but->ShowWindow(false);
		combo->ShowWindow(false);
		currindex = 0;
	}else
	{

		but->ShowWindow(true);
		combo->ShowWindow(true);
		combo->Clear();
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		int ti= pk[currsquad].targetindex;
		if (ti<0) ti=0;
		TargetGroup* trg;
		trg = Node_Data[pk.packagetarget[ti].currentid];
 		combo->AddString(GetTargName(trg->uid));

		for (int i=0; i < TargetGroup::MAXSECONDARIES;i++)
		{
			if	(	(trg)	&&	(trg->secondaries[i]))
				combo->AddString(GetTargName(trg->secondaries[i]));
		}
		combo->SetIndex(0);
		currindex = 0;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}