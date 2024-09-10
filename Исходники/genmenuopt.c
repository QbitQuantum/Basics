static BOOL CALLBACK GenMenuOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct OrderData *dat = (struct OrderData*)GetWindowLong(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWL_USERDATA);

	switch (msg) {
	case WM_INITDIALOG: {

		TranslateDialogDefault(hwndDlg);
		dat=(struct OrderData*)mir_alloc(sizeof(struct OrderData));
		SetWindowLong(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWL_USERDATA,(LONG)dat);
		dat->dragging=0;
		MyOldWindowProc=(WNDPROC)GetWindowLong(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWL_WNDPROC);
		SetWindowLong(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWL_WNDPROC,(LONG)&LBTNDOWNProc);


		//SetWindowLong(GetDlgItem(hwndDlg,IDC_BUTTONORDERTREE),GWL_STYLE,GetWindowLong(GetDlgItem(hwndDlg,IDC_BUTTONORDERTREE),GWL_STYLE)|TVS_NOHSCROLL);

		{   
			HIMAGELIST himlCheckBoxes;
			himlCheckBoxes=ImageList_Create(GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),ILC_COLOR32|ILC_MASK,2,2);
			ImageList_AddIcon(himlCheckBoxes,LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_NOTICK)));
			ImageList_AddIcon(himlCheckBoxes,LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_TICK)));
			TreeView_SetImageList(GetDlgItem(hwndDlg,IDC_MENUOBJECTS),himlCheckBoxes,TVSIL_NORMAL);
			TreeView_SetImageList(GetDlgItem(hwndDlg,IDC_MENUITEMS),himlCheckBoxes,TVSIL_NORMAL);
		}
		BuildMenuObjectsTree(hwndDlg);
		//			Tree
		//			BuildTree(hwndDlg);
		//			OptionsOpened=TRUE;			

		//			OptionshWnd=hwndDlg;
		return TRUE;
							}
	case WM_COMMAND:
		{
			if ((HIWORD(wParam)==BN_CLICKED|| HIWORD(wParam)==BN_DBLCLK)) {
				int ctrlid=LOWORD(wParam);
				if (ctrlid==IDC_INSERTSEPARATOR) {
					InsertSeparator(hwndDlg);
					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				}
				if (ctrlid==IDC_GENMENU_DEFAULT) {

					TVITEM tvi;
					HTREEITEM hti;
					char buf[256];

					hti=TreeView_GetSelection(GetDlgItem(hwndDlg,IDC_MENUITEMS));
					if (hti==NULL)
						break;

					tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
					tvi.hItem=hti;
					TreeView_GetItem(GetDlgItem(hwndDlg,IDC_MENUITEMS),&tvi);

					if ( _tcsstr(((MenuItemOptData *)tvi.lParam)->name, _T("---------------------------------------------")))
						break;

					ZeroMemory(buf,256);
					GetDlgItemTextA(hwndDlg,IDC_GENMENU_CUSTOMNAME,buf,256);
					if (((MenuItemOptData *)tvi.lParam)->name) {
						mir_free(((MenuItemOptData *)tvi.lParam)->name);
					}

					((MenuItemOptData *)tvi.lParam)->name = mir_tstrdup( ((MenuItemOptData *)tvi.lParam)->defname );

					SaveTree(hwndDlg);
					RebuildCurrent(hwndDlg);

				}

				if (ctrlid==IDC_GENMENU_SET) {

					TVITEM tvi;
					TCHAR buf[256];

					HTREEITEM hti = TreeView_GetSelection( GetDlgItem( hwndDlg,IDC_MENUITEMS ));
					if ( hti == NULL )
						break;

					tvi.mask = TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
					tvi.hItem = hti;
					SendDlgItemMessage(hwndDlg, IDC_MENUITEMS, TVM_GETITEM, 0, (LPARAM)&tvi);

					if ( _tcsstr(((MenuItemOptData *)tvi.lParam)->name, STR_SEPARATOR ))
						break;

					ZeroMemory(buf,sizeof( buf ));
					GetDlgItemText( hwndDlg, IDC_GENMENU_CUSTOMNAME, buf, SIZEOF( buf ));
					if (((MenuItemOptData *)tvi.lParam)->name)
						mir_free(((MenuItemOptData *)tvi.lParam)->name);

					((MenuItemOptData *)tvi.lParam)->name = mir_tstrdup(buf);

					SaveTree(hwndDlg);
					RebuildCurrent(hwndDlg);
				}
				break;
			}

			if ((HIWORD(wParam)==STN_CLICKED|| HIWORD(wParam)==STN_DBLCLK)) {
				int ctrlid=LOWORD(wParam);

			}
			break;
		}
	case WM_NOTIFY:
		switch(((LPNMHDR)lParam)->idFrom ) {
		case 0:
			if (((LPNMHDR)lParam)->code == PSN_APPLY ) {   
				SaveTree(hwndDlg);
				RebuildCurrent(hwndDlg);
			}
			break;

		case IDC_MENUOBJECTS:   
			if (((LPNMHDR)lParam)->code == TVN_SELCHANGEDA )
			{
				TVITEM tvi;
				HTREEITEM hti;

				hti=TreeView_GetSelection(GetDlgItem(hwndDlg,IDC_MENUOBJECTS));
				if (hti==NULL)
					break;
				tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
				tvi.hItem=hti;
				TreeView_GetItem(GetDlgItem(hwndDlg,IDC_MENUOBJECTS),&tvi);
				BuildTree(hwndDlg,(int)tvi.lParam);
			}
			break;

		case IDC_MENUITEMS:
			switch (((LPNMHDR)lParam)->code) {
			case NM_CUSTOMDRAW:
				{
					int i= handleCustomDraw(GetDlgItem(hwndDlg,IDC_MENUITEMS),(LPNMTVCUSTOMDRAW) lParam);
					SetWindowLong(hwndDlg, DWL_MSGRESULT, i); 
					return TRUE;
				}

			case TVN_BEGINDRAGA:
				SetCapture(hwndDlg);
				dat->dragging=1;
				dat->hDragItem=((LPNMTREEVIEW)lParam)->itemNew.hItem;
				TreeView_SelectItem(GetDlgItem(hwndDlg,IDC_MENUITEMS),dat->hDragItem);
				//ShowWindow(GetDlgItem(hwndDlg,IDC_BUTTONORDERTREEWARNING),SW_SHOW);
				break;

			case NM_CLICK:
				{
					TVHITTESTINFO hti;
					hti.pt.x=(short)LOWORD(GetMessagePos());
					hti.pt.y=(short)HIWORD(GetMessagePos());
					ScreenToClient(((LPNMHDR)lParam)->hwndFrom,&hti.pt);
					if (TreeView_HitTest(((LPNMHDR)lParam)->hwndFrom,&hti)) {
						if (hti.flags&TVHT_ONITEMICON) {
							TVITEM tvi;
							tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
							tvi.hItem=hti.hItem;
							TreeView_GetItem(((LPNMHDR)lParam)->hwndFrom,&tvi);

							tvi.iImage=tvi.iSelectedImage=!tvi.iImage;
							((MenuItemOptData *)tvi.lParam)->show=tvi.iImage;
							TreeView_SetItem(((LPNMHDR)lParam)->hwndFrom,&tvi);
							SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);

							//all changes take effect in runtime
							//ShowWindow(GetDlgItem(hwndDlg,IDC_BUTTONORDERTREEWARNING),SW_SHOW);
						}
						/*--------MultiSelection----------*/
						if (hti.flags&TVHT_ONITEMLABEL) {
							/// LabelClicked Set/unset selection
							TVITEM tvi;
							HWND tvw=((LPNMHDR)lParam)->hwndFrom;
							tvi.mask=TVIF_HANDLE|TVIF_PARAM;
							tvi.hItem=hti.hItem;
							TreeView_GetItem(tvw,&tvi);
							if (GetKeyState(VK_CONTROL)&0x8000) {
								if (((MenuItemOptData *)tvi.lParam)->isSelected)
									((MenuItemOptData *)tvi.lParam)->isSelected=0;
								else
									((MenuItemOptData *)tvi.lParam)->isSelected=1;  //current selection order++.
								TreeView_SetItem(tvw,&tvi);
							}
							else if (GetKeyState(VK_SHIFT)&0x8000) {
								;  // shifted click
							}
							else {
								// reset all selection except current
								HTREEITEM hit;
								hit=TreeView_GetRoot(tvw);
								if (hit)
									do {
										TVITEM tvi={0};
										tvi.mask=TVIF_HANDLE|TVIF_PARAM;
										tvi.hItem=hit;
										TreeView_GetItem(tvw,&tvi);

										if (hti.hItem!=hit)
											((MenuItemOptData *)tvi.lParam)->isSelected=0;
										else
											((MenuItemOptData *)tvi.lParam)->isSelected=1;
										TreeView_SetItem(tvw,&tvi);
									}
										while (hit=TreeView_GetNextSibling(tvw,hit));
					}	}	}
					break;
				}
			case TVN_SELCHANGING:
				{
					LPNMTREEVIEW pn;
					pn = (LPNMTREEVIEW) lParam;
					//((MenuItemOptData *)(pn->itemNew.lParam))->isSelected=1;
					/*if (pn->action==NotKeyPressed)
					{
					remove all selection
					}
					*/
				}
			case TVN_SELCHANGEDA:
				{
					TVITEM tvi;
					HTREEITEM hti;

					SetDlgItemTextA(hwndDlg,IDC_GENMENU_CUSTOMNAME,"");
					SetDlgItemTextA(hwndDlg,IDC_GENMENU_SERVICE,"");

					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_CUSTOMNAME),FALSE);
					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_DEFAULT),FALSE);
					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_SET),FALSE);

					hti=TreeView_GetSelection(GetDlgItem(hwndDlg,IDC_MENUITEMS));
					if (hti==NULL) {
						EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_CUSTOMNAME),FALSE);
						EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_DEFAULT),FALSE);
						EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_SET),FALSE);
						break;
					}
					tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
					tvi.hItem=hti;
					TreeView_GetItem(GetDlgItem(hwndDlg,IDC_MENUITEMS),&tvi);

					if ( tvi.lParam == 0 )
						break;

					if ( _tcsstr(((MenuItemOptData *)tvi.lParam)->name, STR_SEPARATOR ))
						break;

					SetDlgItemText(hwndDlg,IDC_GENMENU_CUSTOMNAME,((MenuItemOptData *)tvi.lParam)->name);

					SetDlgItemTextA(hwndDlg,IDC_GENMENU_SERVICE,(((MenuItemOptData *)tvi.lParam)->uniqname)?(((MenuItemOptData *)tvi.lParam)->uniqname):"");

					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_DEFAULT),TRUE);
					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_SET),TRUE);
					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_CUSTOMNAME),TRUE);
					break;
				}
				break;
		}	}
		break;

	case WM_MOUSEMOVE:
		if (!dat||!dat->dragging) break;
		{   
			TVHITTESTINFO hti;

			hti.pt.x=(short)LOWORD(lParam);
			hti.pt.y=(short)HIWORD(lParam);
			ClientToScreen(hwndDlg,&hti.pt);
			ScreenToClient(GetDlgItem(hwndDlg,IDC_MENUITEMS),&hti.pt);
			TreeView_HitTest(GetDlgItem(hwndDlg,IDC_MENUITEMS),&hti);
			if (hti.flags&(TVHT_ONITEM|TVHT_ONITEMRIGHT)) {
				HTREEITEM it = hti.hItem;
				hti.pt.y -= TreeView_GetItemHeight(GetDlgItem(hwndDlg,IDC_MENUITEMS))/2;
				TreeView_HitTest(GetDlgItem(hwndDlg,IDC_MENUITEMS),&hti);
				if (!(hti.flags&TVHT_ABOVE))
					TreeView_SetInsertMark(GetDlgItem(hwndDlg,IDC_MENUITEMS),hti.hItem,1);
				else
					TreeView_SetInsertMark(GetDlgItem(hwndDlg,IDC_MENUITEMS),it,0);
			}
			else {
				if (hti.flags&TVHT_ABOVE) SendDlgItemMessage(hwndDlg,IDC_MENUITEMS,WM_VSCROLL,MAKEWPARAM(SB_LINEUP,0),0);
				if (hti.flags&TVHT_BELOW) SendDlgItemMessage(hwndDlg,IDC_MENUITEMS,WM_VSCROLL,MAKEWPARAM(SB_LINEDOWN,0),0);
				TreeView_SetInsertMark(GetDlgItem(hwndDlg,IDC_MENUITEMS),NULL,0);
		}	}
		break;

	case WM_DESTROY:
	{	
		struct OrderData* dat = (struct OrderData*)GetWindowLong( GetDlgItem(hwndDlg,IDC_MENUITEMS), GWL_USERDATA );
		if ( dat )
			mir_free( dat );
		
		FreeTreeData( hwndDlg );
		break;
	}

	case WM_LBUTTONUP:
		if (!dat->dragging)
			break;

		TreeView_SetInsertMark(GetDlgItem(hwndDlg,IDC_MENUITEMS),NULL,0);
		dat->dragging=0;
		ReleaseCapture();
		{   
			TVHITTESTINFO hti;
			hti.pt.x=(short)LOWORD(lParam);
			hti.pt.y=(short)HIWORD(lParam);
			ClientToScreen(hwndDlg,&hti.pt);
			ScreenToClient(GetDlgItem(hwndDlg,IDC_MENUITEMS),&hti.pt);
			hti.pt.y-=TreeView_GetItemHeight(GetDlgItem(hwndDlg,IDC_MENUITEMS))/2;
			TreeView_HitTest(GetDlgItem(hwndDlg,IDC_MENUITEMS),&hti);
			if (hti.flags&TVHT_ABOVE) hti.hItem=TVI_FIRST;
			if (dat->hDragItem==hti.hItem) break;
			dat->hDragItem=NULL;
			if (hti.flags&(TVHT_ONITEM|TVHT_ONITEMRIGHT)||(hti.hItem==TVI_FIRST)) {
				HWND tvw;
				HTREEITEM * pSIT;
				HTREEITEM FirstItem=NULL;
				UINT uITCnt,uSic ;
				tvw=GetDlgItem(hwndDlg,IDC_MENUITEMS);
				uITCnt=TreeView_GetCount(tvw);
				uSic=0;
				if (uITCnt) {
					pSIT=(HTREEITEM *)malloc(sizeof(HTREEITEM)*uITCnt);
					if (pSIT) {
						HTREEITEM hit;
						hit=TreeView_GetRoot(tvw);
						if (hit)
							do {
								TVITEM tvi={0};
								tvi.mask=TVIF_HANDLE|TVIF_PARAM;
								tvi.hItem=hit;
								TreeView_GetItem(tvw,&tvi);                                                
								if (((MenuItemOptData *)tvi.lParam)->isSelected) {
									pSIT[uSic]=tvi.hItem;

									uSic++;
								}
							}while (hit=TreeView_GetNextSibling(tvw,hit));
						// Proceed moving
						{
							UINT i;
							HTREEITEM insertAfter;
							insertAfter=hti.hItem;
							for (i=0; i<uSic; i++) {
								if (insertAfter) insertAfter=MoveItemAbove(tvw,pSIT[i],insertAfter);
								else break;
								if (!i) FirstItem=insertAfter;
						}	}
						// free pointers...
						free(pSIT);
				}	}

				if (FirstItem) TreeView_SelectItem(tvw,FirstItem);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				SaveTree(hwndDlg);
		}	}
		break; 
	}
	return FALSE;
}