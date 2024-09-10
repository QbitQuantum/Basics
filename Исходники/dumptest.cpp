int _tmain(int argc, _TCHAR* argv[])
{
	DWORD aid = 0;
	video_info_t VideoInfo;
	audio_info_t AudioInfo;
	HMODULE hDLL;
	if (argc < 2)
		return 0;
	if (argc > 2)
		aid = _wtoi(argv[2]);
	if (NULL == (hDLL = LoadLibraryA("dshownative.dll")))
		return 0;
	InitDShowGraphFromFile = (TInitDShowGraphFromFile)GetProcAddress(hDLL,"InitDShowGraphFromFileW");
	StartGraph = (TGraphOperate)GetProcAddress(hDLL,"StartGraph");
	StopGraph = (TGraphOperate)GetProcAddress(hDLL,"StopGraph");
	DestroyGraph = (TGraphOperate)GetProcAddress(hDLL,"DestroyGraph");
	if (!(g_pdgi = InitDShowGraphFromFile(argv[1],MEDIASUBTYPE_YV12,0,0,VCallBackProc,CallBackProc,&VideoInfo,&AudioInfo)))
		return 0;
#ifndef _DEBUG
	waveheader.channels = AudioInfo.nChannels;
	waveheader.sample_rate = AudioInfo.nSamplesPerSec;
	waveheader.bits_per_sample = AudioInfo.wBitsPerSample;
	waveheader.block_align = waveheader.channels * waveheader.bits_per_sample / 8;
	waveheader.avg_bytes_sec = waveheader.block_align * waveheader.sample_rate;
	waveheader.format_tag = 0x3;
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteFile(StdOut,&waveheader,sizeof(TWaveHeader),&dwWritten,NULL);
#endif
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	hEvent = CreateEventA(NULL,FALSE,FALSE,NULL);
	StartGraph(g_pdgi);
	WaitForSingleObject(hEvent,INFINITE);
	StopGraph(g_pdgi);DestroyGraph(g_pdgi);
	if (GetFileType(StdOut) == FILE_TYPE_DISK) {
		waveheader.data_size = GetFileSize(StdOut,NULL) - sizeof(TWaveHeader);
		waveheader.size = waveheader.data_size + sizeof(TWaveHeader) - 8;
		SetFilePointer(StdOut,0,NULL,FILE_BEGIN);
		WriteFile(StdOut,&waveheader,sizeof(TWaveHeader),&dwWritten,NULL);
	}
	CloseHandle(StdOut);
	CoUninitialize();
	return 1;
}