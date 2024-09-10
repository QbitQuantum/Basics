BOOL CSQuick2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (_DPlay.PlayerCreated)
	{
//DeadCode AMM 16Nov99 		_DPlay.SendInDebriefMessage();
//DeadCode AMM 16Nov99 		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_DEBRIEF;
		_DPlay.SendStatusChange(DPlay::CPS_DEBRIEF);
	}
	Debrief_Timer=SetTimer(DPlay::TIMER_DEBRIEF,0,NULL);

	
	CRStatic*   s=GETDLGITEM(IDC_SMISSIONTITLE);
	if (CSQuick1::currquickmiss==-1)
//DEADCODE RDH 08/05/00 		s->SetString(RESSTRING(SINGLEPLAYER1));
		s->SetString(RESSTRING(RODS_STRINGS));
	else
		s->SetString(LoadResString(CSQuick1::quickmissions[CSQuick1::currquickmiss].missionname));
	s=GETDLGITEM(IDC_SOBJECTIVETITLE);
	s->SetString(GetTargName(CSQuick1::quickdef.target));

	//clear them out, not used										  //RDH 15/06/99
 	s=GETDLGITEM(IDC_SMISSIONRATING);
	s->SetString("");
	s=GETDLGITEM(IDC_RSTATICCTRL4);
	s->SetString("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}