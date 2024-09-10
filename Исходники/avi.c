avi_str *avi_init(char *out, void *bih, LONG bihl) {
	avi_str *r = malloc(sizeof(avi_str));
	AVIFileInit();
	AVIFileOpenA(&r->fp, out, OF_CREATE | OF_WRITE, NULL);
	AVISTREAMINFO si;
	ZeroMemory(&si, sizeof(AVISTREAMINFO));
	si.fccType = streamtypeVIDEO;
	si.fccHandler = mmioFOURCC('U', 'L', 'R', 'G');
	si.dwScale = 1;
	si.dwRate = GLC_FPS;
	si.dwQuality = -1;
	SetRect(&si.rcFrame, 0, 0, GLC_MAX_WIDTH, GLC_MAX_HEIGHT);
	AVIFileCreateStream(r->fp, &r->sp, &si);
	AVIStreamSetFormat(r->sp, 0, bih, bihl);
	return r;
}