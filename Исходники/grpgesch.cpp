void	GroupGeschwader::RefreshGr13()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->ShowWindow(false);

	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL2);
	rlistbox->Clear();
	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);
	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);
		CRStatic*   s;
	
	s=GETDLGITEM(IDC_RSTATICCTRL7);
	s->ShowWindow(false);
	s=GETDLGITEM(IDC_RSTATICCTRL23);
	s->ShowWindow(false);
//RDH 02/06/99

	rlistbox->AddString(RESSTRING(HURRICANES),0);
	rlistbox->AddString(RESSTRING(SPITFIRES),1);

	FindAirfields();
	int k=0, numsq = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
 		if (Node_Data.squadron[k].homeairfield == Airfields[0][0])
		{
			int actype = Node_Data.squadron[k].AcType();
			int index = 0;
			if	(		(actype == PT_SPIT_A)
					||	(actype == PT_SPIT_B)
				)
				index = 1;
				
			rlistbox->AddString(Node_Data.squadron[k].SubName()+ " "+RESSTRING(SQUADRON),index);
		}

		k++;
	}


}