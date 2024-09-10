LRESULT CALLBACK PortDlgHandler(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	PORTOBJ * st;
	char tmp[20];
	
	st = (PORTOBJ *) actobject;
    if ((st==NULL)||(st->type!=OB_PORT_IO)) return(FALSE);	

	switch( message )
	{
		case WM_INITDIALOG:
				SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_RESETCONTENT,0,0);
			    SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) " LPT1 (378h)") ;
				SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) " LPT2 (278h)") ;
				SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) " LPT3 (3BCh)") ;
				if (st->portaddress==0x378) SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_SETCURSEL, 0, 0L ) ;
				if (st->portaddress==0x278) SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_SETCURSEL, 1, 0L ) ;
				if (st->portaddress==0x3bc) SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_SETCURSEL, 2, 0L ) ;

				SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_RESETCONTENT,0,0);
				SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) "no periodic updates") ;
				SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) "trigger updates") ;
				SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) "bitwise updates") ;
				SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_ADDSTRING, 0,  (LPARAM) (LPSTR) "meter updates") ;
				SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_SETCURSEL, st->triggermode, 0L ) ;

				SetDlgItemInt(hDlg,IDC_VAL0, st->val0,0);
				SetDlgItemInt(hDlg,IDC_VAL1, st->val1,0);
				sprintf(tmp,"%04X",st->portaddress);
				SetDlgItemText(hDlg,IDC_PORTADDRESS, tmp);

				update_bitpositions(hDlg, st->portval);
				
				break;		

		case WM_CLOSE:
			    EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
				case IDC_PORTADDRESSCOMBO:
					if (HIWORD(wParam)==CBN_SELCHANGE)
					{
				     switch (SendDlgItemMessage(hDlg, IDC_PORTADDRESSCOMBO, CB_GETCURSEL, 0, 0 ))
					 {
						case 0: st->portaddress=0x378; break;
						case 1: st->portaddress=0x278; break;
						case 2: st->portaddress=0x3bc; break;
					 }
					 sprintf(tmp,"%04X",st->portaddress);
		 			 SetDlgItemText(hDlg,IDC_PORTADDRESS, tmp);
					}
				  break;

				case IDC_PORTMODECOMBO:
					if (HIWORD(wParam)==CBN_SELCHANGE)
					  st->triggermode= SendDlgItemMessage(hDlg, IDC_PORTMODECOMBO, CB_GETCURSEL, 0, 0 );
					  
					break;
				case IDC_VAL0:
					 st->val0=GetDlgItemInt(hDlg,IDC_VAL0,NULL,0);
					break;
				case IDC_VAL1:
					 st->val1=GetDlgItemInt(hDlg,IDC_VAL1,NULL,0);
					break;

				case IDC_PD7:
					st->portval^=128; 
					outportb (st->portaddress,st->portval);
					break;
				case IDC_PD6:
					st->portval^=64;
					outportb (st->portaddress,st->portval);
					break;
				case IDC_PD5:
					st->portval^=32;
					outportb (st->portaddress,st->portval);
                    break;
				case IDC_PD4:
					st->portval^=16;
					outportb (st->portaddress,st->portval);
                    break;
				case IDC_PD3:
					st->portval^=8;
					outportb (st->portaddress,st->portval);
                    break;
				case IDC_PD2:
					st->portval^=4;
					outportb (st->portaddress,st->portval);
                    break;
				case IDC_PD1:
					st->portval^=2;
					outportb (st->portaddress,st->portval);
                    break;
				case IDC_PD0:
					st->portval^=1;
					outportb (st->portaddress,st->portval);
                    break;

				case IDC_WRITEVAL0:
					outportb (st->portaddress,st->val0);
					st->portval=st->val0;
					update_bitpositions(hDlg, st->portval);
					break;
				case IDC_WRITEVAL1:
					outportb (st->portaddress,st->val1);
					st->portval=st->val1;
					update_bitpositions(hDlg, st->portval);
					break;
				

			}
			return TRUE;
			break;

		case WM_SIZE:
		case WM_MOVE:  update_toolbox_position(hDlg);
		break;
		return(TRUE);
	}
	return FALSE;
}