BOOL LWRouteAirfield::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(80);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddColumn(60);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(LOCATION),1);
	rlistbox->AddString(RESSTRING(ETA),2);
	rlistbox->AddString(RESSTRING(RELTOT),3);
	rlistbox->AddString(RESSTRING(FUEL),4);
	
	rlistbox->AddString("Strike",0);
	rlistbox->AddString("Wissen",1);
	rlistbox->AddString("14:00",2);
	rlistbox->AddString("-01:20",3);
	rlistbox->AddString("3000",4);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}