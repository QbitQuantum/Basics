// window procedure
LRESULT CALLBACK SpectrumWindowProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch (m) {
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEMOVE:
			if (w&MK_LBUTTON) SetLoopStart(LOWORD(l)*bpp); // set loop start
			if (w&MK_RBUTTON) SetLoopEnd(LOWORD(l)*bpp); // set loop end
			return 0;

		case WM_MBUTTONDOWN:
			BASS_ChannelSetPosition(chan,LOWORD(l)*bpp,BASS_POS_BYTE); // set current pos
			return 0;

		case WM_TIMER:
			InvalidateRect(h,0,0); // refresh window
			return 0;

		case WM_PAINT:
			if (GetUpdateRect(h,0,0)) {
				PAINTSTRUCT p;
				HDC dc;
				if (!(dc=BeginPaint(h,&p))) return 0;
				BitBlt(dc,0,0,WIDTH,HEIGHT,wavedc,0,0,SRCCOPY); // draw peak waveform
				DrawTimeLine(dc,loop[0],0xffff00,12); // loop start
				DrawTimeLine(dc,loop[1],0x00ffff,24); // loop end
				DrawTimeLine(dc,BASS_ChannelGetPosition(chan,BASS_POS_BYTE),0xffffff,0); // current pos
				EndPaint(h,&p);
			}
			return 0;

		case WM_CREATE:
			win=h;
			// initialize output
			if (!BASS_Init(-1,44100,0,win,NULL)) {
				Error("Can't initialize device");
				return -1;
			}
			if (!PlayFile()) { // start a file playing
				BASS_Free();
				return -1;
			}
			SetTimer(h,0,100,0); // set update timer (10hz)
			break;

		case WM_DESTROY:
			KillTimer(h,0);
			if (scanthread) { // still scanning
				killscan=TRUE;
				WaitForSingleObject((HANDLE)scanthread,1000); // wait for the thread
			}
			BASS_Free();
			if (wavedc) DeleteDC(wavedc);
			if (wavebmp) DeleteObject(wavebmp);
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(h, m, w, l);
}