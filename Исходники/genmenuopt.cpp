static INT_PTR CALLBACK GenMenuOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct OrderData *dat = (struct OrderData*)GetWindowLongPtr(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWLP_USERDATA);
	LPNMHDR hdr;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		dat=(struct OrderData*)mir_alloc(sizeof(struct OrderData));
		SetWindowLongPtr(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWLP_USERDATA,(LONG_PTR)dat);
		dat->dragging = 0;
		dat->iInitMenuValue = DBGetContactSettingByte( NULL, "CList", "MoveProtoMenus", FALSE );
		MyOldWindowProc = (WNDPROC)GetWindowLongPtr(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWLP_WNDPROC);
		SetWindowLongPtr(GetDlgItem(hwndDlg,IDC_MENUITEMS),GWLP_WNDPROC,(LONG_PTR)&LBTNDOWNProc);
		{
			HIMAGELIST himlCheckBoxes;
			himlCheckBoxes=ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
				(IsWinVerXPPlus() ? ILC_COLOR32 : ILC_COLOR16) | ILC_MASK, 2, 2);

			ImageList_AddIcon_IconLibLoaded(himlCheckBoxes, SKINICON_OTHER_NOTICK);
			ImageList_AddIcon_IconLibLoaded(himlCheckBoxes, SKINICON_OTHER_TICK);

			TreeView_SetImageList(GetDlgItem(hwndDlg,IDC_MENUOBJECTS),himlCheckBoxes,TVSIL_NORMAL);
			TreeView_SetImageList(GetDlgItem(hwndDlg,IDC_MENUITEMS),himlCheckBoxes,TVSIL_NORMAL);
		}
		CheckDlgButton(hwndDlg, dat->iInitMenuValue ? IDC_RADIO2 : IDC_RADIO1, TRUE );
		CheckDlgButton(hwndDlg, IDC_DISABLEMENUICONS, bIconsDisabled );
		BuildMenuObjectsTree(hwndDlg);
		return TRUE;

	case WM_COMMAND:
		if ( HIWORD(wParam) == BN_CLICKED || HIWORD( wParam ) == BN_DBLCLK ) {
			switch ( LOWORD( wParam )) {
			case IDC_INSERTSEPARATOR:
				InsertSeparator(hwndDlg);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_RESETMENU:
				ResetMenuItems( hwndDlg );
				SendMessage( GetParent( hwndDlg ), PSM_CHANGED, 0, 0 );
				break;

			case IDC_DISABLEMENUICONS:
			case IDC_RADIO1:
			case IDC_RADIO2:
				SendMessage( GetParent( hwndDlg ), PSM_CHANGED, 0, 0 );
				break;

			case IDC_GENMENU_DEFAULT:
				{
					TVITEM tvi;
					HTREEITEM hti;
					MenuItemOptData *iod;

					hti=TreeView_GetSelection(GetDlgItem(hwndDlg,IDC_MENUITEMS));
					if (hti==NULL)
						break;

					tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
					tvi.hItem=hti;
					TreeView_GetItem(GetDlgItem(hwndDlg,IDC_MENUITEMS),&tvi);
					iod = ( MenuItemOptData * )tvi.lParam;

					if ( iod->name && _tcsstr( iod->name, STR_SEPARATOR ))
						break;

					if (iod->name)
						mir_free(iod->name);
					iod->name = mir_tstrdup( iod->defname );

					SaveTree(hwndDlg);
					RebuildCurrent(hwndDlg);
					SendMessage( GetParent( hwndDlg ), PSM_CHANGED, 0, 0 );
				}
				break;

			case IDC_GENMENU_SET:
				{
					TVITEM tvi;
					TCHAR buf[256];
					MenuItemOptData *iod;

					HTREEITEM hti = TreeView_GetSelection( GetDlgItem( hwndDlg,IDC_MENUITEMS ));
					if ( hti == NULL )
						break;

					tvi.mask = TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
					tvi.hItem = hti;
					SendDlgItemMessage(hwndDlg, IDC_MENUITEMS, TVM_GETITEM, 0, (LPARAM)&tvi);
					iod = ( MenuItemOptData * )tvi.lParam;

					if ( iod->name && _tcsstr(iod->name, STR_SEPARATOR ))
						break;

					ZeroMemory(buf,sizeof( buf ));
					GetDlgItemText( hwndDlg, IDC_GENMENU_CUSTOMNAME, buf, SIZEOF( buf ));
					if (iod->name)
						mir_free(iod->name);

					iod->name = mir_tstrdup(buf);

					SaveTree(hwndDlg);
					RebuildCurrent(hwndDlg);
					SendMessage( GetParent( hwndDlg ), PSM_CHANGED, 0, 0 );
				}
				break;
		}	}
		break;

	case WM_NOTIFY:
		hdr = (LPNMHDR)lParam;
		switch( hdr->idFrom ) {
		case 0:
			if (hdr->code == PSN_APPLY ) {
				bIconsDisabled = IsDlgButtonChecked(hwndDlg, IDC_DISABLEMENUICONS) != 0;
				DBWriteContactSettingByte(NULL, "CList", "DisableMenuIcons", bIconsDisabled);
				SaveTree(hwndDlg);
				int iNewMenuValue = IsDlgButtonChecked(hwndDlg, IDC_RADIO1) ? 0 : 1;
				if ( iNewMenuValue != dat->iInitMenuValue ) {
					RebuildProtoMenus( iNewMenuValue );
					dat->iInitMenuValue = iNewMenuValue;
				}
				RebuildCurrent(hwndDlg);
			}
			break;

		case IDC_MENUOBJECTS:
			if (hdr->code == TVN_SELCHANGEDA )
				RebuildCurrent( hwndDlg );
			break;

		case IDC_MENUITEMS:
			switch (hdr->code) {
			case NM_CUSTOMDRAW:
				{
					int i= handleCustomDraw(GetDlgItem(hwndDlg,IDC_MENUITEMS),(LPNMTVCUSTOMDRAW) lParam);
					SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, i);
					return TRUE;
				}

			case TVN_BEGINDRAGA:
				SetCapture(hwndDlg);
				dat->dragging=1;
				dat->hDragItem=((LPNMTREEVIEW)lParam)->itemNew.hItem;
				TreeView_SelectItem(GetDlgItem(hwndDlg,IDC_MENUITEMS),dat->hDragItem);
				break;

			case NM_CLICK:
				{
					TVHITTESTINFO hti;
					hti.pt.x=(short)LOWORD(GetMessagePos());
					hti.pt.y=(short)HIWORD(GetMessagePos());
					ScreenToClient(hdr->hwndFrom,&hti.pt);
					if (TreeView_HitTest(hdr->hwndFrom,&hti)) {
						if (hti.flags&TVHT_ONITEMICON) {
							TVITEM tvi;
							tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
							tvi.hItem=hti.hItem;
							TreeView_GetItem(hdr->hwndFrom,&tvi);

							tvi.iImage=tvi.iSelectedImage=!tvi.iImage;
							((MenuItemOptData *)tvi.lParam)->show=tvi.iImage;
							TreeView_SetItem(hdr->hwndFrom,&tvi);
							SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);

							//all changes take effect in runtime
							//ShowWindow(GetDlgItem(hwndDlg,IDC_BUTTONORDERTREEWARNING),SW_SHOW);
						}
						/*--------MultiSelection----------*/
						if (hti.flags&TVHT_ONITEMLABEL) {
							/// LabelClicked Set/unset selection
							TVITEM tvi;
							HWND tvw=hdr->hwndFrom;
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
					MenuItemOptData *iod;

					SetDlgItemTextA(hwndDlg,IDC_GENMENU_CUSTOMNAME,"");
					SetDlgItemTextA(hwndDlg,IDC_GENMENU_SERVICE,"");

					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_CUSTOMNAME),FALSE);
					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_DEFAULT),FALSE);
					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_SET),FALSE);

					hti=TreeView_GetSelection(GetDlgItem(hwndDlg,IDC_MENUITEMS));
					if (hti==NULL)
						break;

					tvi.mask=TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
					tvi.hItem=hti;
					TreeView_GetItem(GetDlgItem(hwndDlg,IDC_MENUITEMS),&tvi);

					if ( tvi.lParam == 0 )
						break;

					iod = ( MenuItemOptData * )tvi.lParam;

					if ( iod->name && _tcsstr(iod->name, STR_SEPARATOR))
						break;

					SetDlgItemText(hwndDlg,IDC_GENMENU_CUSTOMNAME,iod->name);

					if (iod->pimi->submenu.first == NULL && iod->uniqname)
						SetDlgItemTextA(hwndDlg, IDC_GENMENU_SERVICE, iod->uniqname);

					EnableWindow(GetDlgItem(hwndDlg,IDC_GENMENU_DEFAULT), lstrcmp(iod->name, iod->defname) != 0);
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
					pSIT=(HTREEITEM *)mir_alloc(sizeof(HTREEITEM)*uITCnt);
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
						mir_free(pSIT);
				}	}

				if (FirstItem) TreeView_SelectItem(tvw,FirstItem);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				SaveTree(hwndDlg);
		}	}
		break;

	case WM_DESTROY:
		if ( dat )
			mir_free( dat );

		ImageList_Destroy(TreeView_SetImageList(GetDlgItem(hwndDlg,IDC_MENUOBJECTS),NULL,TVSIL_NORMAL));
		FreeTreeData( hwndDlg );
		break;

	}
	return FALSE;
}