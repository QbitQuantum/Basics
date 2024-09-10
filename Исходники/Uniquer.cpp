int CALLBACK OptionsDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg==WM_INITDIALOG){
		iBegin=0;
		iBegin2=0;
		hDiag=hwndDlg;
		bAutoDelRight=0;
		if(GetKeyState(VK_CONTROL)<0){
			bReplaceMode=1;
		}
		::SetWindowText(GetDlgItem(hwndDlg,IDC_STATUS),CString(" ")+_l("Preparing for search"));
		::SetWindowText(GetDlgItem(hwndDlg,IDC_IMGL_DEL),_l("Delete this image"));
		::SetWindowText(GetDlgItem(hwndDlg,IDC_IMGR_DEL),_l("Delete this image"));
		::SetWindowText(GetDlgItem(hwndDlg,IDC_IMGR_DEL_ALL),_l("Auto"));
		::SetWindowText(GetDlgItem(hwndDlg,IDC_LI_ST),_l("No image, please wait"));
		::SetWindowText(GetDlgItem(hwndDlg,IDC_RI_ST),_l("No image, please wait"));
		if(bReplaceMode){
			::SetWindowText(GetDlgItem(hwndDlg,ID_NEXT),"Stop renamer");
		}else{
			::SetWindowText(GetDlgItem(hwndDlg,ID_NEXT),_l("Stop processing"));
		}
		::SetWindowText(hwndDlg,_l("Search for duplicated images"));
		::EnableWindow(GetDlgItem(hwndDlg,IDC_IMGR_DEL_ALL),FALSE);
		::EnableWindow(GetDlgItem(hwndDlg,IDC_IMGL_DEL),FALSE);
		::EnableWindow(GetDlgItem(hwndDlg,IDC_IMGR_DEL),FALSE);
		SetTaskbarButton(hwndDlg);
		//::EnableWindow(GetDlgItem(hwndDlg,ID_NEXT),FALSE);
	}
	if(uMsg==WM_KEYDOWN){
		if(GetKeyState(VK_CONTROL)<0){
			if(wParam==VK_RETURN){
				uMsg=WM_COMMAND;
				wParam=IDOK;
			}
		}
	}
	if(bStopCheck==0){
		if(uMsg==WM_COMMAND && wParam==WM_USER){
			// Выбираем у кого разрешение ниже...
			CString sPath;
			if(dwPathInRightRes<dwPathInLeftRes){
				uMsg=WM_COMMAND;
				wParam=IDC_IMGR_DEL;
			}else{
				uMsg=WM_COMMAND;
				wParam=IDC_IMGL_DEL;
			}
		}
		if(uMsg==WM_COMMAND && wParam==IDC_IMGL_DEL){
			if(IsWindowEnabled(GetDlgItem(hwndDlg,IDC_IMGL_DEL))){
				if(sPathInLeft!=""){
					sListOfImagesToDelete.Add(sPathInLeft);
				}
			}
			sPathInLeft="";
			sPathInRight="";
			uMsg=WM_COMMAND;
			wParam=ID_NEXT;
		}
		if(uMsg==WM_COMMAND && wParam==IDC_IMGR_DEL){
			if(IsWindowEnabled(GetDlgItem(hwndDlg,IDC_IMGR_DEL))){
				if(sPathInRight!=""){
					sListOfImagesToDelete.Add(sPathInRight);
				}
			}
			sPathInLeft="";
			sPathInRight="";
			uMsg=WM_COMMAND;
			wParam=ID_NEXT;
		}
		if(uMsg==WM_COMMAND && wParam==IDC_IMGR_DEL_ALL){
			if(bAutoDelRight || AfxMessageBox(_l("Delete duplicated images automatically")+"?",MB_YESNO|MB_ICONQUESTION)==IDYES){
				bAutoDelRight=1-bAutoDelRight;
				if(bAutoDelRight){
					::SetWindowText(GetDlgItem(hwndDlg,IDC_IMGR_DEL_ALL),_l("Stop"));
					PostMessage(hwndDlg,WM_COMMAND,WM_USER,0);
				}else{
					::SetWindowText(GetDlgItem(hwndDlg,IDC_IMGR_DEL_ALL),_l("Auto"));
				}
			}
		}
		if(uMsg==WM_COMMAND && wParam==ID_NEXT){
			if(iMode==0){
				bStopLoad=1;
			}else if(bStopCheck==0){
				iBegin2++;
				::EnableWindow(GetDlgItem(hwndDlg,IDC_IMGL_DEL),FALSE);
				::EnableWindow(GetDlgItem(hwndDlg,IDC_IMGR_DEL),FALSE);
				::EnableWindow(GetDlgItem(hwndDlg,ID_NEXT),FALSE);
				FORK(ContinueCheck,hwndDlg);
			}
		}
	}
	if(uMsg==WM_PAINT){
		PAINTSTRUCT lpPaint;
		memset(&lpPaint,0,sizeof(lpPaint));
		HDC dcH=BeginPaint(hwndDlg,&lpPaint);
		CDC dc;
		dc.Attach(lpPaint.hdc);
		dc.SetStretchBltMode(HALFTONE);
		//DefWindowProc(
		if(sPathInLeft!=""){
			if(btLeft){
				CRect rt,rtw;
				::GetClientRect(GetDlgItem(hwndDlg,IDC_IMGL),&rt);
				::GetWindowRect(GetDlgItem(hwndDlg,IDC_IMGL),&rtw);
				CPoint ptLT(rtw.left,rtw.top);
				ScreenToClient(hwndDlg,&ptLT);
				CDC dc2;
				CDesktopDC dcDesk;
				dc2.CreateCompatibleDC(&dcDesk);
				CBitmap* bmpTmp=dc2.SelectObject(btLeft);
				FitImageToRect(rt,szLeftSize);
				dc.StretchBlt(ptLT.x+rt.left,ptLT.y+rt.top,rt.Width(),rt.Height(),&dc2,0,0,szLeftSize.cx,szLeftSize.cy,SRCCOPY);
				dc2.SelectObject(bmpTmp);
			}
		}
		if(sPathInRight!=""){
			if(btRight){
				CRect rt,rtw;
				::GetClientRect(GetDlgItem(hwndDlg,IDC_IMGR),&rt);
				::GetWindowRect(GetDlgItem(hwndDlg,IDC_IMGR),&rtw);
				CPoint ptLT(rtw.left,rtw.top);
				ScreenToClient(hwndDlg,&ptLT);
				CDC dc2;
				CDesktopDC dcDesk;
				dc2.CreateCompatibleDC(&dcDesk);
				CBitmap* bmpTmp=dc2.SelectObject(btRight);
				FitImageToRect(rt,szLeftSize);
				dc.StretchBlt(ptLT.x+rt.left,ptLT.y+rt.top,rt.Width(),rt.Height(),&dc2,0,0,szRightSize.cx,szRightSize.cy,SRCCOPY);
				dc2.SelectObject(bmpTmp);
			}
		}
		dc.Detach();
		EndPaint(hwndDlg,&lpPaint);
		return TRUE;
	}
	if(uMsg==WM_SYSCOMMAND && wParam==SC_CLOSE){
		uMsg=WM_COMMAND;
		wParam=IDOK;
	}
	if(uMsg==WM_COMMAND && wParam==IDOK){
		bStopCheck=1;
		csCheck.Lock();
		csCheck.Unlock();
		if(sListOfImagesToDelete.GetSize()>0){
			if(dwDeleteOptions){
				if(AfxMessageBox(Format("%s. %s: %i\n%s?",_l("Search for duplicated images: finished"),_l("Image(s) found"),sListOfImagesToDelete.GetSize(),_l("Do you really want to delete image(s)")),MB_YESNO|MB_ICONQUESTION)==IDYES){
					for(int i=0;i<sListOfImagesToDelete.GetSize();i++){
						char szPath[MAX_PATH+2]="";
						memset(&szPath,0,sizeof(szPath));
						strcpy(szPath,sListOfImagesToDelete[i]);
						if(isFileExist(szPath)){
							SHFILEOPSTRUCT str;
							memset(&str,0,sizeof(str));
							str.hwnd=hwndDlg;
							str.wFunc=FO_DELETE;
							str.pFrom=szPath;
							str.pTo=NULL;
							str.fFlags=FOF_ALLOWUNDO|FOF_NOCONFIRMATION|FOF_SILENT;
							SHFileOperation(&str);
							lDeletedFiles++;
						}
					}
				}
			}else{
				lDeletedFiles+=sListOfImagesToDelete.GetSize();
			}
		}
		if(bReplaceMode){
			CString sDump;
			int ik=0;
			for(ik=0;ik<aClosestImage.GetSize();ik++){
				sDump+=Format("%i -> %i, %i %s\n",ik,aClosestImage[ik],aClosestImageTaken[ik],sListOfImages[ik]);
				aClosestImageTaken[ik]=0;
			}
			int iCnt=0;
			int iJumper=-1;
			CStringArray aFrom;
			CStringArray aFromTo;
			while(1){
				if(iJumper==-1){
					// Ищем первую картинку
					for(ik=0;ik<aClosestImage.GetSize();ik++){
						if(aClosestImageTaken[ik]==0){
							iJumper=ik;
							break;
						}
					}
				}
				if(iJumper==-1){
					// Не нашли!!
					break;
				}
				aClosestImageTaken[iJumper]=1;// Чтобы не циклится
				int iNext=aClosestImage[iJumper];
				if(iNext==-1 || aClosestImageTaken[iNext]!=0){
					iJumper=-1;
					continue;
				}
				CString sFrom=sListOfImages[iJumper];
				CString sTo=Format("%s%05i_%s",GetPathPart(sFrom,1,1,0,0),iCnt+1,GetPathPart(sFrom,0,0,1,1));
				aFrom.SetAtGrow(iCnt,sFrom);
				aFromTo.SetAtGrow(iCnt,sTo);
				sDump+=Format("Jumping %i -> %i\n",iJumper,iNext);
				iJumper=iNext;
				iCnt++;
			}
			SaveFile("f:\\rename.txt",sDump);
			for(int i=0;i<aFrom.GetSize();i++)
			{
				if(isFileExist(aFrom[i])){
					SHFILEOPSTRUCT str;
					memset(&str,0,sizeof(str));
					str.hwnd=hwndDlg;
					str.wFunc=FO_RENAME;
					
					char szPath[MAX_PATH+2]="";
					memset(&szPath,0,sizeof(szPath));
					strcpy(szPath,aFrom[i]);
					str.pFrom=szPath;
					
					char szPath2[MAX_PATH+2]="";
					memset(&szPath2,0,sizeof(szPath2));
					strcpy(szPath2,aFromTo[i]);
					str.pTo=szPath2;
					str.fFlags=FOF_NOCONFIRMATION|FOF_SILENT;
					SHFileOperation(&str);
				}
			}

		}
		EndDialog(hwndDlg,0);
		return TRUE;
	}
	if(uMsg==WM_NCDESTROY){
		SetEvent(hStopEvent);
	}
	return FALSE;
}