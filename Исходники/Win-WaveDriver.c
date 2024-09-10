ULONG GetPos(MADDriverRec *WinMADDriver)
{
	MMTIME mmt;
	mmt.wType = TIME_BYTES;
	
	waveOutGetPosition(WinMADDriver->hWaveOut, &mmt,sizeof(MMTIME));
	
	return(mmt.u.cb & 0xfffffff0);		// A cause du 16 bits??
}