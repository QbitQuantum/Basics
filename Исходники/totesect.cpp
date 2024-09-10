void ToteSector::RefreshLights()
{
  
	CRect parentpos(1,1,0,0);
	GetWindowRect(parentpos);
	parentpos.top=1;
	CPoint parentoff(-parentpos.left,parentpos.top);
	
	
	enum{MAXSQUAD = 4, MAXAIRFIELDS = 10};
	SquadNum	squad[MAXSQUAD];
	UniqueID	Airfields[MAXAIRFIELDS];
	TargetFighterField* af = Node_Data[sectoraf];

	int m = 0;
	Airfields[m++] = sectoraf;
	while (		((af = af->nextsatelite())!= NULL)
				&&	(m < MAXAIRFIELDS)
		  )
	   Airfields[m++]= af->uid;
	while	(m < MAXAIRFIELDS)
		Airfields[m++]= UID_Null;

	int j=0, k = 0;
	m = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
		for (m = 0; m < MAXAIRFIELDS; m++)
		{
			if (Node_Data.squadron[k].homeairfield == Airfields[m])
			{
			  squad[j++] = Node_Data.squadron[k].squadron;
			}
		}
	  k++;
	}




	BritSquadron* sq;
	int  i =0;
	CRButton* bb;
	CRButton* bw;
	CRStatic*   sn;
	CRStatic*   sp;
	CRStatic*   sa;

	while (i < 5)
	{
		switch(i)
		{
			default_neverreferenced;
			case 0:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W0);
				bb = GETDLGITEM(IDC_RBUTTON_B0);
				sn=GETDLGITEM(IDC_RSTATICSQ0);
				sp=GETDLGITEM(IDC_RSTATIC_PLT0);
				sa=GETDLGITEM(IDC_RSTATIC_AC0);
				break;
			}
			case 1:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W1);
				bb = GETDLGITEM(IDC_RBUTTON_B1);
				sn=GETDLGITEM(IDC_RSTATICSQ1);
				sp=GETDLGITEM(IDC_RSTATIC_PLT1);
				sa=GETDLGITEM(IDC_RSTATIC_AC1);
				break;
			}
			case 2:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W2);
				bb = GETDLGITEM(IDC_RBUTTON_B2);
				sn=GETDLGITEM(IDC_RSTATICSQ2);
				sp=GETDLGITEM(IDC_RSTATIC_PLT2);
				sa=GETDLGITEM(IDC_RSTATIC_AC2);
				break;
			}
			case 3:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W3);
				bb = GETDLGITEM(IDC_RBUTTON_B3);
				sn=GETDLGITEM(IDC_RSTATICSQ3);
				sp=GETDLGITEM(IDC_RSTATIC_PLT3);
				sa=GETDLGITEM(IDC_RSTATIC_AC3);
				break;
			}
			case 4:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W4);
				bb = GETDLGITEM(IDC_RBUTTON_B4);
				sn=GETDLGITEM(IDC_RSTATICSQ4);
				sp=GETDLGITEM(IDC_RSTATIC_PLT4);
				sa=GETDLGITEM(IDC_RSTATIC_AC4);
				break;
			}


		}

				if (i<j)
				{
					sq = Node_Data[squad[i]];

					sn->SetString(sq->SubName());
			
					sp->SetString(CSprintf("%i", sq->pilotsavail));

					sa->SetString(CSprintf("%i", sq->acavail));
				

					bw->ShowWindow(true);
					bb->ShowWindow(true);

					CRect dlistpos;
					bw->GetWindowRect(dlistpos);

					int status = sq->totestatus;
					int index = readinesslevel[status];
					if (index < 9)
						index = 76+ index *28;
					else
						index = 392 + ((index - 9) * 28);
					parentoff.y=parentpos.top+(index)-dlistpos.top;

					SLong hr, mins;
					hr = MMC.currtime / SECSPERHR;
					mins = ((MMC.currtime- (SECSPERHR * hr)) / SECSPERMIN);
					SWord ind = mins %15;
					ind = ind /5;
					ind = 3 - ind;
					if (sq->totestatus<Profile::PS_PLANNED)
					{
						int max=sq->acavail;
						if (max>sq->pilotsavail)
							max=sq->pilotsavail;
						if (max>15)
							max=15;
						max=max/3;
						dlistpos.right=dlistpos.left+(max*10);
						ind=0;
					}
					else
					{
						int availbits=sq->usedacbits;
						int avail = Bit_Count_Nibble[availbits&15];
						avail += Bit_Count_Nibble[(availbits>>4)&15];
						avail += Bit_Count_Nibble[(availbits>>8)&15];
						avail/=3;
						dlistpos.right=dlistpos.left+(avail*10);

					}
					dlistpos+=parentoff;
					bw->MoveWindow(dlistpos);
					
					bb->GetWindowRect(dlistpos);

					bb->SetNormalFileNum(ICON_BTOTE+ind-1);
					parentoff.y=parentpos.top+316+(ind*14)-dlistpos.top;
					dlistpos+=parentoff;
					bb->MoveWindow(dlistpos);
				}else
				{