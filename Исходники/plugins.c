BOOL CALLBACK dialogproc(HWND h,UINT m,WPARAM w,LPARAM l)
{
	switch (m) {
		case WM_COMMAND:
			switch (LOWORD(w)) {
				case IDCANCEL:
					DestroyWindow(h);
					break;
				case 10:
					{
						char file[MAX_PATH]="";
						ofn.lpstrFile=file;
						ofn.nMaxFile=MAX_PATH;
						if (GetOpenFileName(&ofn)) {
							BASS_StreamFree(chan); // free the old stream
							if (!(chan=BASS_StreamCreateFile(FALSE,file,0,0,BASS_SAMPLE_LOOP))) {
								// it ain't playable
								MESS(10,WM_SETTEXT,0,"click here to open a file...");
								MESS(11,WM_SETTEXT,0,"");
								Error("Can't play the file");
								break;
							}
							MESS(10,WM_SETTEXT,0,file);
							{ // display the file type and length
								QWORD bytes=BASS_ChannelGetLength(chan,BASS_POS_BYTE);
								DWORD time=BASS_ChannelBytes2Seconds(chan,bytes);
								BASS_CHANNELINFO info;
								BASS_ChannelGetInfo(chan,&info);
								sprintf(file,"channel type = %x (%s)\nlength = %I64u (%u:%02u)",
									info.ctype,GetCTypeString(info.ctype,info.plugin),bytes,time/60,time%60);
								MESS(11,WM_SETTEXT,0,file);
								MESS(12,TBM_SETRANGE,1,MAKELONG(0,time)); // update scroller range
							}
							BASS_ChannelPlay(chan,FALSE);
						}
					}
					break;
			}
			break;

		case WM_HSCROLL:
			if (l && LOWORD(w)!=SB_THUMBPOSITION && LOWORD(w)!=SB_ENDSCROLL) { // set the position
				int pos=SendMessage((HWND)l,TBM_GETPOS,0,0);
				BASS_ChannelSetPosition(chan,BASS_ChannelSeconds2Bytes(chan,pos),BASS_POS_BYTE);
			}
			break;

		case WM_TIMER:
			MESS(12,TBM_SETPOS,1,(DWORD)BASS_ChannelBytes2Seconds(chan,BASS_ChannelGetPosition(chan,BASS_POS_BYTE))); // update position
			break;

		case WM_INITDIALOG:
			win=h;
			// initialize default output device
			if (!BASS_Init(-1,44100,0,win,NULL)) {
				Error("Can't initialize device");
				DestroyWindow(win);
				break;
			}
			// initialize file selector
			memset(&ofn,0,sizeof(ofn));
			ofn.lStructSize=sizeof(ofn);
			ofn.hwndOwner=h;
			ofn.Flags=OFN_HIDEREADONLY|OFN_EXPLORER;
			ofn.lpstrFilter=filter;
			memcpy(filter,"BASS built-in (*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif)\0*.mp3;*.mp2;*.mp1;*.ogg;*.wav;*.aif\0",88);
			{ // look for plugins (in the executable's directory)
				WIN32_FIND_DATA fd;
				HANDLE fh;
				char path[MAX_PATH],*fp=filter+88;
				GetModuleFileName(0,path,sizeof(path));
				strcpy(strrchr(path,'\\')+1,"bass*.dll");
				fh=FindFirstFile(path,&fd);
				if (fh!=INVALID_HANDLE_VALUE) {
					do {
						HPLUGIN plug;
						if (plug=BASS_PluginLoad(fd.cFileName,0)) { // plugin loaded...
							const BASS_PLUGININFO *pinfo=BASS_PluginGetInfo(plug); // get plugin info to add to the file selector filter...
							int a;
							for (a=0;a<pinfo->formatc;a++) {
								fp+=sprintf(fp,"%s (%s) - %s",pinfo->formats[a].name,pinfo->formats[a].exts,fd.cFileName)+1; // format description
								fp+=sprintf(fp,"%s",pinfo->formats[a].exts)+1; // extension filter
							}
							// add plugin to the list
							MESS(20,LB_ADDSTRING,0,fd.cFileName);
						}
					} while (FindNextFile(fh,&fd));
					FindClose(fh);
				}
				if (!MESS(20,LB_GETCOUNT,0,0)) // no plugins...
					MESS(20,LB_ADDSTRING,0,"no plugins - visit the BASS webpage to get some");
				memcpy(fp,"All files\0*.*\0\0",15);
			}
			SetTimer(h,0,500,0); // timer to update the position
			return 1;

		case WM_DESTROY:
			// "free" the output device and all plugins
			BASS_Free();
			BASS_PluginFree(0);
			break;
	}
	return 0;
}