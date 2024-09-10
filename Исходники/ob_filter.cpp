LRESULT CALLBACK FilterboxDlgHandler( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	int t; // ,z;
	char newname[25],sztemp[30];
	static int acttype;
	static int dinit=FALSE;
	static FidFilter * tempf=NULL,* newf=NULL;
    
	FILTEROBJ * st;
	
	st = (FILTEROBJ *) actobject;
    if ((st==NULL)||(st->type!=OB_FILTER)) return(FALSE);

	switch( message )
	{
		case WM_INITDIALOG:
				dinit=TRUE;
				SendMessage(GetDlgItem(hDlg, IDC_FILTERTYPECOMBO), CB_RESETCONTENT,0,0);
			    for (t = 0; t < FILTERTYPES; t++) 
					SendMessage( GetDlgItem(hDlg, IDC_FILTERTYPECOMBO), CB_ADDSTRING, 0,  (LPARAM) (LPSTR) FILTERTYPE[t].tname) ;

				SetDlgItemText(hDlg,IDC_FILTERTYPECOMBO, FILTERTYPE[st->filtertype].tname);
				SetDlgItemText(hDlg,IDC_FILTERNEWNAME, st->name);
				SetDlgItemInt(hDlg,IDC_FROMFREQ, st->dispfrom,0);
				SetDlgItemInt(hDlg,IDC_TOFREQ, st->dispto,0);
				SetDlgItemInt(hDlg,IDC_FILTERPAR0, st->par0,0);
				sprintf(sztemp,"%.5f",st->par1);
				SetDlgItemText(hDlg,IDC_FILTERPAR1, sztemp);
				sprintf(sztemp,"%.5f",st->par2);
				SetDlgItemText(hDlg,IDC_FILTERPAR2, sztemp);
				acttype=st->filtertype;
				dinit=FALSE;
				newf=do_filt_design(hDlg,acttype);
				if (newf) tempf=newf;
				update_filterdialog(hDlg,st->filtertype);				
				return TRUE;
		case WM_CLOSE:		
			    EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			
			case IDC_FILTERTYPECOMBO:
				  acttype=SendMessage( GetDlgItem(hDlg, IDC_FILTERTYPECOMBO), CB_GETCURSEL, 0, 0 ) ;
				  update_filterdialog(hDlg,acttype);
			case IDC_FILTERPAR0:
			case IDC_FILTERPAR1:
			case IDC_FILTERPAR2:
			case IDC_FROMFREQ:
			case IDC_TOFREQ:
				if (!dinit)
				{
					newf=do_filt_design(hDlg,acttype);
					if (newf) tempf=newf;
 					InvalidateRect(hDlg,NULL,TRUE);
				}
				break;
			case IDC_FILTERSTORE:
				if (newf)
				{
					GetDlgItemText(hDlg, IDC_FILTERNEWNAME,newname,sizeof(newname));
				
					st->filtertype=acttype;
					st->par0=GetDlgItemInt(hDlg,IDC_FILTERPAR0, NULL, 0);
					GetDlgItemText(hDlg,IDC_FILTERPAR1,sztemp,sizeof(sztemp)); 
					sscanf(sztemp,"%f",&st->par1);
					GetDlgItemText(hDlg,IDC_FILTERPAR2,sztemp,sizeof(sztemp));
					st->dispfrom=GetDlgItemInt(hDlg, IDC_FROMFREQ, NULL, 0);
					st->dispto=GetDlgItemInt(hDlg, IDC_TOFREQ, NULL, 0);
					sscanf(sztemp,"%f",&st->par2);
					strcpy(st->name,newname);

					st->filt=do_filt_design(hDlg, acttype);
					st->run= fid_run_new(st->filt, &(st->funcp));
					if (st->fbuf!=NULL)
					{
						fid_run_freebuf(st->fbuf);
   						st->fbuf=fid_run_newbuf(st->run);
					}
				}
				break;
				}
				return(TRUE);
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc;
				RECT rect;
				HPEN	 tpen;
				HBRUSH	 tbrush;
				int height;
				int f1,f2;
				float fstep,val,x;

				hdc = BeginPaint (hDlg, &ps);
				GetClientRect(hDlg, &rect);
				tpen    = CreatePen (PS_SOLID,1,0);
				SelectObject (hdc, tpen);
				tbrush  = CreateSolidBrush(RGB(240,240,240));
				SelectObject(hdc,tbrush);
				rect.top+=80;
				rect.bottom -= 18;
				height= rect.bottom-rect.top;
				Rectangle(hdc,rect.left,rect.top-1,rect.right,rect.bottom+20);
				Rectangle(hdc,rect.left,rect.top-1,rect.right,rect.bottom);
				Rectangle(hdc,rect.left,rect.bottom-(int)(height/1.3),rect.right,rect.bottom);
				
				DeleteObject(tbrush);
				DeleteObject(tpen);

				tpen = CreatePen (PS_SOLID,1,RGB(0,100,0));
				SelectObject (hdc, tpen);
				f1=GetDlgItemInt(hDlg, IDC_FROMFREQ, NULL, 0);
				f2=GetDlgItemInt(hDlg, IDC_TOFREQ, NULL, 0);
				fstep=(float)(f2-f1)/(rect.right-rect.left);
				MoveToEx(hdc,rect.left+1,rect.bottom-(int)(height*fid_response(tempf, (float)f1/256.0)/1.3),NULL);
				for (t=rect.left; t<rect.right; t++)
				{ 
					MoveToEx(hdc,1+t,rect.bottom,NULL);
					LineTo(hdc,1+t,rect.bottom-(int)(height*fid_response(tempf, (((float)f1+fstep*(t-rect.left))/PACKETSPERSECOND))/1.3));
				}
				SelectObject(hdc, DRAW.scaleFont);
				wsprintf(sztemp,"1.0"); 
				ExtTextOut( hdc, rect.left+2,rect.top+(int)(height*0.2308), 0, &rect,sztemp, strlen(sztemp), NULL ) ;
				val=(f2-f1)/10.0f;
				fstep=((rect.right-25)-rect.left)/10.0f;
				for (t=0; t<=10; t++)
				{ 
					x=f1+val*t;
					wsprintf(sztemp,"%d.%d",(int)x,(int)(x*10)%10); 
					ExtTextOut( hdc, rect.left+2+(int)(fstep*t),rect.bottom+2, 0, &rect,sztemp, strlen(sztemp), NULL ) ;
				}
				DeleteObject(tpen);
				EndPaint(hDlg, &ps );
				}
				break;
		case WM_SIZE:
		case WM_MOVE:  update_toolbox_position(hDlg);
		break;
		return(TRUE);
	}
    return FALSE;
}