LRESULT CLegoBrickPropertiesWnd::OnPropertyChanged (WPARAM,LPARAM lParam)
{    
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;

	//do something 
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd();
	HTREEITEM hSelected = pFrame->GetClassView()->GetTreeView()->GetSelectedItem();
	LBInfoNode* pBrickNode = (LBInfoNode*)pFrame->GetClassView()->GetTreeView()->GetItemData(hSelected);

	CString str;
	if (pProp == pPropType) {
		CString strType = (LPCTSTR)(_bstr_t)pProp->GetValue();
		for (int i=0; i<NUMOFBRICKTYPE; i++) {
			if (strType == strmap[i].str)
				pBrickNode->bi.brick.type = strmap[i].bt;
		}

		int idxImage, idxSelImage;

		CViewTree* pTreeCtrl = pFrame->GetClassView()->GetTreeView();
		pTreeCtrl->GetItemImage(hSelected, idxImage, idxSelImage);
		DWORD_PTR data = pTreeCtrl->GetItemData(hSelected);

		str = pFrame->GetClassView()->MakeLegoBrickString(&(pBrickNode->bi));

		HTREEITEM hNewItem;	

		// notype
		if (pBrickNode->bi.brick.type == NOTYPE) {
			hNewItem = pTreeCtrl->InsertItem(str, idxImage, idxSelImage,
				TVI_ROOT, TVI_LAST);
			pTreeCtrl->SetItemData(hNewItem, data);
		}

		// one row brick
		else if (pBrickNode->bi.brick.type >= ONE_BY_ONE && pBrickNode->bi.brick.type <= ONE_BY_TWELVE) {
			hNewItem = pTreeCtrl->InsertItem(str, idxImage, idxSelImage, 
				pFrame->GetClassView()->hRoot1, TVI_SORT);
			pTreeCtrl->SetItemData(hNewItem, data);
			pTreeCtrl->Expand(pFrame->GetClassView()->hRoot1, TVE_EXPAND);
		}
		// two row brick
		else {
			hNewItem = pTreeCtrl->InsertItem(str, idxImage, idxSelImage, 
				pFrame->GetClassView()->hRoot2, TVI_SORT);
			pTreeCtrl->SetItemData(hNewItem, data);
			pTreeCtrl->Expand(pFrame->GetClassView()->hRoot2, TVE_EXPAND);
		}
		pTreeCtrl->DeleteItem(hSelected);
		pTreeCtrl->SelectItem(hNewItem);
	
//		pFrame->GetClassView()->GetTreeView()->SetItemText(hSelected, str);
	}

	if (pProp == pPropColor) {
//		pBrickNode->bi.brick.color = ((CMFCPropertyGridColorProperty*)pProp)->GetColor();
		pBrickNode->bi.brick.color = ((CPHPropertyGridColorProperty*)pProp)->GetColor();

		// Get LEGO Color, if NULL -> Not a LEGO color
		pBrickNode->bi.brick.pLegoColor = ((CPHPropertyGridColorProperty*)pProp)->GetLegoColor();


		CBitmap bmp;
		BYTE bits[960];		// typedef unsigned char BTTE;   4*16*15 = 960
		BYTE bits2[960];	// for selected
		pFrame->GetClassView()->BuildTwoBitsBlocks(pBrickNode->bi.brick.color, bits, bits2);
			
		bmp.CreateBitmap(16, 15, 1, 32, bits /*Points to a short-integer array */);
		int idxImage, idxSelImage;
		pFrame->GetClassView()->GetTreeView()->GetItemImage(hSelected, idxImage, idxSelImage);
		pFrame->GetClassView()->GetImageList()->Replace(idxImage, &bmp, NULL); 

		bmp.SetBitmapBits(960, bits2);
		pFrame->GetClassView()->GetImageList()->Replace(idxSelImage, &bmp, NULL); 

		pFrame->GetClassView()->GetTreeView()->SetImageList(
			pFrame->GetClassView()->GetImageList(), TVSIL_NORMAL);

		str = pFrame->GetClassView()->MakeLegoBrickString(&(pBrickNode->bi));
		pFrame->GetClassView()->GetTreeView()->SetItemText(hSelected, str);
	}

	if (pProp == pPropNum) {
		pBrickNode->bi.numBricks = (int) pProp->GetValue().intVal;

		str = pFrame->GetClassView()->MakeLegoBrickString(&(pBrickNode->bi));
		pFrame->GetClassView()->GetTreeView()->SetItemText(hSelected, str);
	}
	if (&(pBrickNode->bi) != NULL)
		pBrickNode->bi.brick.SetID();

	return 0;   
}