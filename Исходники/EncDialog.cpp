BOOL CALLBACK DIALOGMsgProcEnc(HWND hWndDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		{
		char buf[50];
		char *Quality[]={"Default","10","20","30","40","50","60","70","80","90","100","110","120","130","140","150","200","300","400","500",0};
		char *BitRate[]={"Auto","8","18","20","24","32","40","48","56","64","96","112","128","160","192","224","256","320","384",0};
		char *BandWidth[]={"Auto","Full","4000","8000","11025","16000","22050","24000","32000","44100","48000",0};
		CMyEncCfg cfg(false);
			
			SetWindowPos(GetDlgItem(hWndDlg,IDC_CHK_TAG),GetDlgItem(hWndDlg,IDC_GRP_TAG),0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

			INIT_CB(hWndDlg,IDC_CB_QUALITY,Quality,0);
			INIT_CB(hWndDlg,IDC_CB_BITRATE,BitRate,0);
			INIT_CB(hWndDlg,IDC_CB_BANDWIDTH,BandWidth,0);

			INIT_CB_GENRES(hWndDlg,IDC_CB_GENRE,ID3Genres,0);

			SendMessage(GetDlgItem(hWndDlg, IDC_BTN_ARTFILE), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBmBrowse);
#ifdef IDC_BTN_BROWSE			
			SendMessage(GetDlgItem(hWndDlg, IDC_BTN_BROWSE), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBmBrowse);
			if(!cfg.OutDir || !*cfg.OutDir)
			{
				GetCurrentDirectory(MAX_PATH,config_AACoutdir);
				FREE_ARRAY(cfg.OutDir);
				cfg.OutDir=strdup(config_AACoutdir);
			}
			else
				strcpy(config_AACoutdir,cfg.OutDir);
			SetDlgItemText(hWndDlg, IDC_E_BROWSE, cfg.OutDir);			
#endif
			if(cfg.EncCfg.mpegVersion==MPEG4)
				CheckDlgButton(hWndDlg,IDC_RADIO_MPEG4,TRUE);
			else
				CheckDlgButton(hWndDlg,IDC_RADIO_MPEG2,TRUE);
			
			switch(cfg.EncCfg.aacObjectType)
			{
			case MAIN:
				CheckDlgButton(hWndDlg,IDC_RADIO_MAIN,TRUE);
				break;
			case LOW:
				CheckDlgButton(hWndDlg,IDC_RADIO_LOW,TRUE);
				break;
			case SSR:
				CheckDlgButton(hWndDlg,IDC_RADIO_SSR,TRUE);
				break;
			case LTP:
				CheckDlgButton(hWndDlg,IDC_RADIO_LTP,TRUE);
				DISABLE_LTP
				break;
			}
			
			switch(cfg.EncCfg.outputFormat)
			{
			case RAW:
				CheckDlgButton(hWndDlg,IDC_RADIO_RAW,TRUE);
				break;
			case ADTS:
				CheckDlgButton(hWndDlg,IDC_RADIO_ADTS,TRUE);
				break;
			}
			
			CheckDlgButton(hWndDlg, IDC_CHK_ALLOWMIDSIDE, cfg.EncCfg.allowMidside);
			CheckDlgButton(hWndDlg, IDC_CHK_USETNS, cfg.EncCfg.useTns);
			CheckDlgButton(hWndDlg, IDC_CHK_USELFE, cfg.EncCfg.useLfe);

			if(cfg.UseQuality)
				CheckDlgButton(hWndDlg,IDC_RADIO_QUALITY,TRUE);
			else
				CheckDlgButton(hWndDlg,IDC_RADIO_BITRATE,TRUE);

			switch(cfg.EncCfg.quantqual)
			{
			case 100:
				SendMessage(GetDlgItem(hWndDlg, IDC_CB_QUALITY), CB_SETCURSEL, 0, 0);
				break;
			default:
				if(cfg.EncCfg.quantqual<10)
					cfg.EncCfg.quantqual=10;
				if(cfg.EncCfg.quantqual>500)
					cfg.EncCfg.quantqual=500;
				sprintf(buf,"%lu",cfg.EncCfg.quantqual);
				SetDlgItemText(hWndDlg, IDC_CB_QUALITY, buf);
				break;
			}
			switch(cfg.EncCfg.bitRate)
			{
			case 0:
				SendMessage(GetDlgItem(hWndDlg, IDC_CB_BITRATE), CB_SETCURSEL, 0, 0);
				break;
			default:
				sprintf(buf,"%lu",cfg.EncCfg.bitRate);
				SetDlgItemText(hWndDlg, IDC_CB_BITRATE, buf);
				break;
			}
			switch(cfg.EncCfg.bandWidth)
			{
			case 0:
				SendMessage(GetDlgItem(hWndDlg, IDC_CB_BANDWIDTH), CB_SETCURSEL, 0, 0);
				break;
			case 0xffffffff:
				SendMessage(GetDlgItem(hWndDlg, IDC_CB_BANDWIDTH), CB_SETCURSEL, 1, 0);
				break;
			default:
				sprintf(buf,"%lu",cfg.EncCfg.bandWidth);
				SetDlgItemText(hWndDlg, IDC_CB_BANDWIDTH, buf);
				break;
			}
			
			CheckDlgButton(hWndDlg, IDC_CHK_WRITEMP4, cfg.SaveMP4);

			CheckDlgButton(hWndDlg,IDC_CHK_AUTOCFG, cfg.AutoCfg);
			DISABLE_CTRLS_ENC(!cfg.AutoCfg);

			CheckDlgButton(hWndDlg,IDC_CHK_TAG, cfg.TagOn);
			ENABLE_TAG(cfg.TagOn);
			ENABLE_AACTAGS(cfg.SaveMP4);
			SetDlgItemText(hWndDlg, IDC_E_ARTIST, cfg.Tag.artist);
			SetDlgItemText(hWndDlg, IDC_E_TITLE, cfg.Tag.title);
			SetDlgItemText(hWndDlg, IDC_E_ALBUM, cfg.Tag.album);
			SetDlgItemText(hWndDlg, IDC_E_YEAR, cfg.Tag.year);
			SetDlgItemText(hWndDlg, IDC_CB_GENRE, cfg.Tag.genre);
			SetDlgItemText(hWndDlg, IDC_E_WRITER, cfg.Tag.writer);
			SetDlgItemText(hWndDlg, IDC_E_COMMENT, cfg.Tag.comment);
			SetDlgItemText(hWndDlg, IDC_E_ARTFILE, cfg.Tag.artFilename);
			SetDlgItemInt(hWndDlg, IDC_E_TRACK, cfg.Tag.trackno, FALSE);
			SetDlgItemInt(hWndDlg, IDC_E_NTRACKS, cfg.Tag.ntracks, FALSE);
			SetDlgItemInt(hWndDlg, IDC_E_DISK, cfg.Tag.discno, FALSE);
			SetDlgItemInt(hWndDlg, IDC_E_NDISKS, cfg.Tag.ndiscs, FALSE);
			SetDlgItemInt(hWndDlg, IDC_E_COMPILATION, cfg.Tag.compilation, FALSE);
			CheckDlgButton(hWndDlg, IDC_CHK_COMPILATION, cfg.Tag.compilation);
		}
		break; // End of WM_INITDIALOG                                 
		
	case WM_CLOSE:
		// Closing the Dialog behaves the same as Cancel               
		PostMessage(hWndDlg, WM_COMMAND, IDCANCEL, 0L);
		break; // End of WM_CLOSE                                      
		
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			{
//			HANDLE hCfg=(HANDLE)lParam;
			char buf[50];
			CMyEncCfg cfg;

				cfg.AutoCfg=IsDlgButtonChecked(hWndDlg,IDC_CHK_AUTOCFG) ? TRUE : FALSE;
				cfg.EncCfg.mpegVersion=IsDlgButtonChecked(hWndDlg,IDC_RADIO_MPEG4) ? MPEG4 : MPEG2;
				if(IsDlgButtonChecked(hWndDlg,IDC_RADIO_MAIN))
					cfg.EncCfg.aacObjectType=MAIN;
				if(IsDlgButtonChecked(hWndDlg,IDC_RADIO_LOW))
					cfg.EncCfg.aacObjectType=LOW;
				if(IsDlgButtonChecked(hWndDlg,IDC_RADIO_SSR))
					cfg.EncCfg.aacObjectType=SSR;
				if(IsDlgButtonChecked(hWndDlg,IDC_RADIO_LTP))
					cfg.EncCfg.aacObjectType=LTP;
				cfg.EncCfg.allowMidside=IsDlgButtonChecked(hWndDlg, IDC_CHK_ALLOWMIDSIDE);
				cfg.EncCfg.useTns=IsDlgButtonChecked(hWndDlg, IDC_CHK_USETNS);
				cfg.EncCfg.useLfe=IsDlgButtonChecked(hWndDlg, IDC_CHK_USELFE);
				
				GetDlgItemText(hWndDlg, IDC_CB_BITRATE, buf, 50);
				switch(*buf)
				{
				case 'A': // Auto
					cfg.EncCfg.bitRate=0;
					break;
				default:
					cfg.EncCfg.bitRate=GetDlgItemInt(hWndDlg, IDC_CB_BITRATE, 0, FALSE);
				}
				GetDlgItemText(hWndDlg, IDC_CB_BANDWIDTH, buf, 50);
				switch(*buf)
				{
				case 'A': // Auto
					cfg.EncCfg.bandWidth=0;
					break;
				case 'F': // Full
					cfg.EncCfg.bandWidth=0xffffffff;
					break;
				default:
					cfg.EncCfg.bandWidth=GetDlgItemInt(hWndDlg, IDC_CB_BANDWIDTH, 0, FALSE);
				}
				cfg.UseQuality=IsDlgButtonChecked(hWndDlg,IDC_RADIO_QUALITY) ? TRUE : FALSE;
				GetDlgItemText(hWndDlg, IDC_CB_QUALITY, buf, 50);
				switch(*buf)
				{
				case 'D': // Default
					cfg.EncCfg.quantqual=100;
					break;
				default:
					cfg.EncCfg.quantqual=GetDlgItemInt(hWndDlg, IDC_CB_QUALITY, 0, FALSE);
				}
				cfg.EncCfg.outputFormat=IsDlgButtonChecked(hWndDlg,IDC_RADIO_RAW) ? RAW : ADTS;
#ifdef IDC_E_BROWSE
				GetDlgItemText(hWndDlg, IDC_E_BROWSE, config_AACoutdir, MAX_PATH);
				FREE_ARRAY(cfg.OutDir);
				cfg.OutDir=strdup(config_AACoutdir);
#endif
				cfg.SaveMP4=IsDlgButtonChecked(hWndDlg, IDC_CHK_WRITEMP4) ? TRUE : FALSE;

				cfg.TagOn=IsDlgButtonChecked(hWndDlg,IDC_CHK_TAG) ? 1 : 0;
			char buffer[MAX_PATH];
				GetDlgItemText(hWndDlg, IDC_E_ARTIST, buffer, MAX_PATH);
				cfg.Tag.artist=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_E_TITLE, buffer, MAX_PATH);
				cfg.Tag.title=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_E_ALBUM, buffer, MAX_PATH);
				cfg.Tag.album=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_E_YEAR, buffer, MAX_PATH);
				cfg.Tag.year=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_CB_GENRE, buffer, MAX_PATH);
				cfg.Tag.genre=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_E_WRITER, buffer, MAX_PATH);
				cfg.Tag.writer=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_E_COMMENT, buffer, MAX_PATH);
				cfg.Tag.comment=strdup(buffer);
				GetDlgItemText(hWndDlg, IDC_E_ARTFILE, buffer, MAX_PATH);
				cfg.Tag.artFilename=strdup(buffer);
				cfg.Tag.trackno=GetDlgItemInt(hWndDlg, IDC_E_TRACK, 0, FALSE);
				cfg.Tag.ntracks=GetDlgItemInt(hWndDlg, IDC_E_NTRACKS, 0, FALSE);
				cfg.Tag.discno=GetDlgItemInt(hWndDlg, IDC_E_DISK, 0, FALSE);
				cfg.Tag.ndiscs=GetDlgItemInt(hWndDlg, IDC_E_NDISKS, 0, FALSE);
				cfg.Tag.compilation=(BYTE)GetDlgItemInt(hWndDlg, IDC_E_COMPILATION, 0, FALSE);
				cfg.Tag.compilation=IsDlgButtonChecked(hWndDlg, IDC_CHK_COMPILATION) ? 1 : 0;

				EndDialog(hWndDlg, TRUE);//(DWORD)hCfg);
			}
			break;
			
        case IDCANCEL:
			// Ignore data values entered into the controls        
			// and dismiss the dialog window returning FALSE
			EndDialog(hWndDlg, FALSE);
			break;

		case IDC_BTN_ABOUT:
			DialogBox((HINSTANCE)hInstance,(LPCSTR)MAKEINTRESOURCE(IDD_ABOUT), (HWND)hWndDlg, (DLGPROC)DialogMsgProcAbout);
			break;

		case IDC_BTN_LICENSE:
			{
			char *license =
				"\nPlease note that the use of this software may require the payment of patent royalties.\n"
				"You need to consider this issue before you start building derivative works.\n"
				"We are not warranting or indemnifying you in any way for patent royalities!\n"
				"YOU ARE SOLELY RESPONSIBLE FOR YOUR OWN ACTIONS!\n"
				"\n"
				"FAAC is based on the ISO MPEG-4 reference code. For this code base the\n"
				"following license applies:\n"
				"\n"
/*				"This software module was originally developed by\n"
				"\n"
				"FirstName LastName (CompanyName)\n"
				"\n"
				"and edited by\n"
				"\n"
				"FirstName LastName (CompanyName)\n"
				"FirstName LastName (CompanyName)\n"
				"\n"
*/				"in the course of development of the MPEG-2 NBC/MPEG-4 Audio standard\n"
				"ISO/IEC 13818-7, 14496-1,2 and 3. This software module is an\n"
				"implementation of a part of one or more MPEG-2 NBC/MPEG-4 Audio tools\n"
				"as specified by the MPEG-2 NBC/MPEG-4 Audio standard. ISO/IEC gives\n"
				"users of the MPEG-2 NBC/MPEG-4 Audio standards free license to this\n"
				"software module or modifications thereof for use in hardware or\n"
				"software products claiming conformance to the MPEG-2 NBC/ MPEG-4 Audio\n"
				"standards. Those intending to use this software module in hardware or\n"
				"software products are advised that this use may infringe existing\n"
				"patents. The original developer of this software module and his/her\n"
				"company, the subsequent editors and their companies, and ISO/IEC have\n"
				"no liability for use of this software module or modifications thereof\n"
				"in an implementation. Copyright is not released for non MPEG-2\n"
				"NBC/MPEG-4 Audio conforming products. The original developer retains\n"
				"full right to use the code for his/her own purpose, assign or donate\n"
				"the code to a third party and to inhibit third party from using the\n"
				"code for non MPEG-2 NBC/MPEG-4 Audio conforming products. This\n"
				"copyright notice must be included in all copies or derivative works.\n"
				"\n"
				"Copyright (c) 1997.\n"
				"\n"
				"For the changes made for the FAAC project the GNU Lesser General Public\n"
				"License (LGPL), version 2 1991 applies:\n"
				"\n"
				"FAAC - Freeware Advanced Audio Coder\n"
				"Copyright (C) 2001-2004 The individual contributors\n"
				"\n"
				"This library is free software; you can redistribute it and/or modify it under the terms of\n"
				"the GNU Lesser General Public License as published by the Free Software Foundation;\n"
				"either version 2.1 of the License, or (at your option) any later version.\n"
				"\n"
				"This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;\n"
				"without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
				"See the GNU Lesser General Public License for more details.\n"
				"\n"
				"You should have received a copy of the GNU Lesser General Public\n"
				"License along with this library; if not, write to the Free Software\n"
				"Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n";

				MessageBox(hWndDlg,license,"FAAC libray License",MB_OK|MB_ICONINFORMATION);
			}
			break;

#ifdef IDC_BTN_BROWSE
		case IDC_BTN_BROWSE:
			{
			char name[MAX_PATH];
			BROWSEINFO bi;
			ITEMIDLIST *idlist;
				bi.hwndOwner = hWndDlg;
				bi.pidlRoot = 0;
				bi.pszDisplayName = name;
				bi.lpszTitle = "Select a directory for AAC-MPEG4 file output:";
				bi.ulFlags = BIF_RETURNONLYFSDIRS;
				bi.lpfn = BrowseCallbackProc;
				bi.lParam = 0;
				
				GetDlgItemText(hWndDlg, IDC_E_BROWSE, config_AACoutdir, MAX_PATH);
				idlist = SHBrowseForFolder( &bi );
				if(idlist)
				{
					SHGetPathFromIDList( idlist, config_AACoutdir);
					SetDlgItemText(hWndDlg, IDC_E_BROWSE, config_AACoutdir);
				}
			}
			break;
#endif			
		case IDC_BTN_ARTFILE:
			{
			OPENFILENAME ofn;
			char ArtFilename[MAX_PATH]="";

//				GetDlgItemText(hWndDlg, IDC_E_ARTFILE, ArtFilename, MAX_PATH);

				ofn.lStructSize			= sizeof(OPENFILENAME);
				ofn.hwndOwner			= (HWND)hWndDlg;
				ofn.lpstrFilter			= "Cover art files (*.gif,*jpg,*.png)\0*.gif;*.jpg;*.png\0";
				ofn.lpstrCustomFilter	= NULL;
				ofn.nFilterIndex		= 1;
				ofn.lpstrFile			= ArtFilename;
				ofn.nMaxFile			= MAX_PATH; //sizeof ArtFilename;
				ofn.lpstrFileTitle		= NULL;
				ofn.nMaxFileTitle		= 0;
				ofn.lpstrInitialDir		= NULL;
				ofn.lpstrTitle			= "Select cover art file";
				ofn.Flags				= OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ENABLESIZING;
				ofn.lpstrDefExt			= NULL;//"jpg";
				ofn.hInstance			= hInstance;

				if(GetOpenFileName(&ofn))
					SetDlgItemText(hWndDlg, IDC_E_ARTFILE, ArtFilename);
			}
			break;

		case IDC_RADIO_MPEG4:
			EnableWindow(GetDlgItem(hWndDlg, IDC_RADIO_LTP), !IsDlgButtonChecked(hWndDlg,IDC_CHK_AUTOCFG));
			break;
			
		case IDC_RADIO_MPEG2:
			EnableWindow(GetDlgItem(hWndDlg, IDC_RADIO_LTP), FALSE);
			DISABLE_LTP
			break;

		case IDC_CHK_AUTOCFG:
			{
			char Enabled=!IsDlgButtonChecked(hWndDlg,IDC_CHK_AUTOCFG);
				DISABLE_CTRLS_ENC(Enabled);
			}
			break;

		case IDC_CHK_TAG:
			{
			char Enabled=IsDlgButtonChecked(hWndDlg,IDC_CHK_TAG);
				ENABLE_TAG(Enabled);
			}
//			break;
		case IDC_CHK_WRITEMP4:
			{
			char Enabled=IsDlgButtonChecked(hWndDlg,IDC_CHK_WRITEMP4) && IsDlgButtonChecked(hWndDlg,IDC_CHK_TAG);
				ENABLE_AACTAGS(Enabled);
			}
			break;
		}
		break; // End of WM_COMMAND
	default: 
		return FALSE;
	}
	
	return TRUE;
} // End of DIALOGSMsgProc                                      