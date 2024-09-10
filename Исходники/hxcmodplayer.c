LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	char file[512];
	WAVEHDR * pwhOut;
	MMTIME mmt;
	unsigned long * framebuf;

	switch (message) // switch selon le message
	{
		case WM_CREATE:
			SetTimer(hWnd,0,10,NULL);
		break;

		case WM_DROPFILES:
			file[0] = 0;
			DragQueryFile((HDROP)wParam, 0, (char*)file, sizeof(file));
			loadmod(file);
		break;

		case WM_TIMER:
			mmt.wType = TIME_SAMPLES;
			if(waveOutGetPosition(wout,&mmt,sizeof(MMTIME)) == MMSYSERR_NOERROR)
			{
				file[0] = 0;

				if(IsWindowVisible(hWnd) && fg)
				{
					if(mmt.u.sample&NBSTEREO16BITSAMPLES)
					{
						framebuf = fg_generateFrame(fg,&trackbuf_state2,mmt.u.sample&(NBSTEREO16BITSAMPLES-1));
					}
					else
					{
						framebuf = fg_generateFrame(fg,&trackbuf_state1,mmt.u.sample&(NBSTEREO16BITSAMPLES-1));
					}

					updateScreen(hWnd, framebuf, fg->xres,fg->yres);
				}
			}
		break;
		case WM_COMMAND:	//Action sur un menu
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch(wmId)
			{
				case IDI_PLAY:
					waveOutRestart(wout);
				break;
				case IDI_PAUSE:
					waveOutPause(wout);
				break;
				case IDI_EJECT:
					file[0] = 0;
					if(fileselector(hWnd,file,"Load mod file","*.mod","*.mod",0,0))
					{
						loadmod(file);
					}
				break;
				case IDI_INFO:
				break;
				case IDI_FILTER:
				break;
				case IDI_STEREO:
				break;

				case IDI_QUIT:
					PostQuitMessage(0);
				break;

			}
		break;

		case WM_DESTROY:
		break;

		case WM_USER: //Message venant de l'icone de la barre des taches
			switch(lParam)
			{
				case WM_LBUTTONDOWN:
					if(GetFocus() == hWnd)
					{
						ShowWindow(hWnd,SW_HIDE);
					}
					else
					{
						ShowWindow(hWnd,SW_SHOWNORMAL);
						SetFocus(hWnd);
					}
				break;
				case WM_RBUTTONDOWN:
					ListPopup(hWnd);
				break;
			}

		break;

		case WM_USER+1:
		break;

		case WM_CLOSE: //message de fermeture
			ShowWindow(hWnd,SW_HIDE);
		break;

		case WM_MOUSEMOVE:
		break;

		case MM_WOM_OPEN:
		break;

		case MM_WOM_CLOSE:
		break;

		case MM_WOM_DONE:
			pwhOut = (struct wavehdr_tag *)lParam;
		
			if(pwhOut->lpData == (char*)&sndbuffer1)
			{
				trackbuf_state1.nb_of_state = 0;
				hxcmod_fillbuffer(&modloaded,(unsigned short*)pwhOut->lpData, pwhOut->dwBufferLength /4,&trackbuf_state1);
			}
			else
			{
				trackbuf_state2.nb_of_state = 0;
				hxcmod_fillbuffer(&modloaded,(unsigned short*)pwhOut->lpData, pwhOut->dwBufferLength /4,&trackbuf_state2);
			}

			waveOutWrite((HWAVEOUT)wParam,pwhOut,sizeof(WAVEHDR));
			nb_wr_block++;

		break;

		case WM_KEYDOWN:
		break;

		default: // traitement par defaut de l'evenement (gerer par windows)
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}