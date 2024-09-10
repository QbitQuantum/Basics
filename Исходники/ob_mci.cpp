LRESULT CALLBACK MCIDlgHandler(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char szFileName[MAX_PATH];
	MCIOBJ * st;
	
	st = (MCIOBJ *) actobject;
    if ((st==NULL)||(st->type!=OB_MCIPLAYER)) return(FALSE);

	switch( message ) 
	{
	case WM_INITDIALOG:
			SetDlgItemText(hDlg, IDC_MCIFILE, st->mcifile);
			SCROLLINFO lpsi;
		    lpsi.cbSize=sizeof(SCROLLINFO);
			lpsi.fMask=SIF_RANGE|SIF_POS;
			lpsi.nMin=4; lpsi.nMax=5000;
			SetScrollInfo(GetDlgItem(hDlg,IDC_SPEEDUPDATEBAR),SB_CTL,&lpsi, TRUE);
			SetScrollPos(GetDlgItem(hDlg,IDC_SPEEDUPDATEBAR), SB_CTL,st->upd_speed, TRUE);
			SetDlgItemInt(hDlg, IDC_UPDATESPEED, st->upd_speed, FALSE);
			SetDlgItemInt(hDlg, IDC_POS_CENTER, st->pos_center, FALSE);
			CheckDlgButton(hDlg, IDC_PLAY_ONCE, st->play_once);
		return TRUE;
        
	case WM_CLOSE:
		 EndDialog(hDlg, LOWORD(wParam));
		break;
    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		  case IDC_OPEN:
			  if (!(strcmp(st->mcifile,"none")))
			  {
				strcpy(szFileName,GLOBAL.resourcepath);
				strcat(szFileName,"MOVIES\\*.avi");
			  } else strcpy (szFileName,st->mcifile);

			if (open_file_dlg(hDlg, szFileName, FT_AVI, OPEN_LOAD)) 
			{

				st->playing=FALSE;
				strcpy(st->mcifile,szFileName);
				SetDlgItemText(hDlg, IDC_MCIFILE, st->mcifile); 
			}
			InvalidateRect(hDlg,NULL,FALSE);
			break;
		  case IDC_PLAY_ONCE:
			  st->play_once=IsDlgButtonChecked(hDlg,IDC_PLAY_ONCE);
			  break;
		    case IDC_LOAD:
				if (st->m_video) {	MCIWndStop(st->m_video); 	MCIWndDestroy(st->m_video); }
				
				st->m_video = MCIWndCreate(ghWndMain, hInst,WS_VISIBLE|WS_THICKFRAME|MCIWNDF_NOERRORDLG,st->mcifile);

				if (!st->m_video)  report_error ("Cannot open MCI File");
				else
				{
					RECT prc;

					MCIWndSetZoom(st->m_video,100);
					MCIWndGetSource(st->m_video,&prc);
					MCIWndSetTimeFormat(st->m_video ,"ms");
					MCIWndSetActiveTimer(st->m_video,500);
					if ((!strstr(st->mcifile,".mp3")) && (!strstr(st->mcifile,".wav"))) 
						SetWindowPos(st->m_video,HWND_TOPMOST,st->left,st->top,st->left+prc.right-prc.left,st->top+prc.bottom-prc.top,SWP_SHOWWINDOW);
					else ShowWindow(st->m_video,FALSE);
					
				}
				break;
			case IDC_MCIPLAY:
					
				if (st->m_video)
				{
					MCIWndSetSpeed(st->m_video,st->speed);
					MCIWndPlay(st->m_video);
					st->playing=TRUE;
				}
		 		break;
				case IDC_MCISTOP:
					if (st->m_video) {	MCIWndStop(st->m_video);}  //	MCIWndDestroy(st->m_video); }
					st->playing=FALSE;
					break;

				case IDC_MCIPLUS:
					st->speed+=50;
					if (st->m_video) { 
						MCIWndSetSpeed(st->m_video,st->speed); //MCIWndStep(st->m_video,2); 
						MCIWndPlay(st->m_video); }
					break;

				case IDC_MCIMINUS:
					st->speed-=50;
					if (st->m_video) 	{  MCIWndSetSpeed(st->m_video,st->speed); 		//MCIWndStep(st->m_video,2); 
					MCIWndPlay(st->m_video);
					}
					break;
				case IDC_POS_CENTER:
					st->pos_center=GetDlgItemInt(hDlg,IDC_POS_CENTER,0,FALSE);

					break;

		}
		break;
	
		case WM_HSCROLL:
		{
			int nNewPos; 
			nNewPos = get_scrollpos(wParam,lParam);
			if (lParam == (long) GetDlgItem(hDlg,IDC_SPEEDUPDATEBAR))  
			{
					SetDlgItemInt(hDlg, IDC_UPDATESPEED, nNewPos, TRUE);
                    st->upd_speed=nNewPos;
			}
			break;
		}

		case WM_SIZE:
		case WM_MOVE:  update_toolbox_position(hDlg);
		break;

	}
   return FALSE;
}