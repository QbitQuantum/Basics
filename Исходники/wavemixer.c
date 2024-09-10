static void DrawWave(struct client *pc, HDC hdc, WPARAM wParam){
#if 0
	int k;
	MMTIME mmtime;
	RECT rr = {320, 320, 320 + 32, 320 + 32};
	mmtime.wType = TIME_SAMPLES;
	waveOutGetPosition(pc->hwo, &mmtime, sizeof mmtime);
	SetBkColor(hdc, !mmtime.u.sample ? RGB(255,0,0) : RGB(0,255,0));
	ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rr, NULL, 0, NULL);
	rr.left += 32;
	rr.right += 32;
	for(k = 0; k < 2; k++){
		SetBkColor(hdc, (~(whs[k].dwFlags | ~(/*WHDR_PREPARED |*/ WHDR_DONE))) | (whs[k].dwFlags & WHDR_INQUEUE) ? RGB(255,0,0) : RGB(0,255,0));
		rr.left += k * 32;
		rr.right += k * 32;
		ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rr, NULL, 0, NULL);
	}
#endif
#if 1
	int i, t;
	{
		MMTIME mmt;
		mmt.wType = TIME_SAMPLES;
		waveOutGetPosition(pc->hwo, &mmt, sizeof mmt);
		t = mmt.u.sample % numof(soundbuf[0]);
	}
	SetBkColor(hdc, RGB(127, 127, 127));
	RECT rr = {320, 320, 320 + 256, 320 + 256};
	ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rr, NULL, 0, NULL);
	for(i = 0; i < 256; i++){
		if(i == t * numof(soundbuf[0]) / 256)
			SelectObject(hdc, GetStockObject(WHITE_PEN));
		MoveToEx(hdc, 320 + i, 320 + 128, NULL);
		LineTo(hdc, 320 + i, 320 + ((BYTE*)((WAVEHDR*)wParam)->lpData)[i * numof(soundbuf[0]) / 256]);
	}
#endif
}