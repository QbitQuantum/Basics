void CompositeDlg::LoadDialog(BOOL draw) 
	{	
	if (theTex) {		
		theTex->ClampOffset();
		
		SetScrollRange(hScroll,SB_CTL,0,theTex->subTex.Count()-NDLG,FALSE);
		SetScrollPos(hScroll,SB_CTL,theTex->offset,TRUE);
		EnableWindow(hScroll,theTex->NumSubTexmaps()>NDLG);

		if (theTex->subTex.Count()>NDLG) {
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_UP),theTex->offset>0);
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_PAGEUP),theTex->offset>0);
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_DOWN),theTex->offset+NDLG<theTex->subTex.Count());
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_PAGEDOWN),theTex->offset+NDLG<theTex->subTex.Count());
		} else {
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_UP),FALSE);
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_PAGEUP),FALSE);
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_DOWN),FALSE);
			EnableWindow(GetDlgItem(hPanel,IDC_COMP_PAGEDOWN),FALSE);
			}

		Interval valid;
		theTex->Update(ip->GetTime(),valid);		
		UpdateSubTexNames();
		TSTR buf;
		buf.printf(_T("%d"),theTex->subTex.Count());
		SetDlgItemText(hPanel,IDC_COMP_NUMMAPS,buf);
		for (int i=0; i<min(theTex->subTex.Count(),NDLG); i++) {
			ShowWindow(GetDlgItem(hPanel,mapIDs[i]),SW_SHOW);
			ShowWindow(GetDlgItem(hPanel,labelIDs[i]),SW_SHOW);
			ShowWindow(GetDlgItem(hPanel,mapOnIDs[i]),SW_SHOW);
//			SetCheckBox(hPanel, mapOnIDs[i], theTex->mapOn[i+theTex->offset]);
			}
		for (; i<NDLG; i++) {
			ShowWindow(GetDlgItem(hPanel,mapIDs[i]),SW_HIDE);
			ShowWindow(GetDlgItem(hPanel,labelIDs[i]),SW_HIDE);
			ShowWindow(GetDlgItem(hPanel,mapOnIDs[i]),SW_HIDE);
			}
		}
	}