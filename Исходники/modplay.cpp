ModPlay::~ModPlay()
{
	stopped = true; // tell the thread to exit
	waveOutPause(hWaveOut); // make sure no buffers are written and played in case of a race condition
	waveOutReset(hWaveOut); // calls WOM_DONE for all buffers (thread checks if stopped == true and exits)
	WaitForSingleObject(hThread, INFINITE); // Let the thread finish
	waveOutClose(hWaveOut);
	CloseHandle(hEventDone);
	CloseHandle(hThread);
	ModPlug_Unload(modFile);
}