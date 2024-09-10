static void WIN_PlayStop(void)
{
	if (hwaveout) waveOutReset(hwaveout);
	VC_PlayStop();
}