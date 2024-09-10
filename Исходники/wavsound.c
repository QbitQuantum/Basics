int playWAVEFile(const char *lpszWAVEFileName)
{
	static int init = 0;
	static HWND hwStopper;
	static int counter = 0;
    DWORD dwReturn;
    MCI_OPEN_PARMS mciOpenParms;
    MCI_PLAY_PARMS mciPlayParms;

    // Open the device by specifying the device and filename.
    // MCI will choose a device capable of playing the specified file.

	if(!init){
		WNDCLASS wc = {
			0, /* UINT       style; */
			SoundStopper, /*WNDPROC    lpfnWndProc; */
			0, /*int        cbClsExtra; */
			0, /*int        cbWndExtra; */
			NULL, /*HINSTANCE  hInstance; */
			NULL, /*HICON      hIcon; */
			NULL, /*HCURSOR    hCursor; */
			NULL, /*HBRUSH     hbrBackground; */
			NULL, /*LPCTSTR    lpszMenuName; */
			"SoundStopperClass", /*LPCTSTR    lpszClassName; */
		}; 
		ATOM atom;
		wc.hInstance = (HINSTANCE)GetModuleHandle(NULL);;

		if(!(atom = RegisterClass(&wc)) ||
			!(hwStopper = CreateWindow((LPCTSTR)atom, "SoundStopper", 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL))){
			MsgBoxErr();
			return 1;
		}
		init = 1;
	}

	{
		WCHAR alias[5];
		alias[0] = '0' + counter % 10;
		alias[1] = '0' + counter / 10 % 10;
		alias[2] = '0' + counter / 10 / 10 % 10;
		alias[3] = '\0';
		counter++;
		mciOpenParms.lpstrDeviceType = "waveaudio";
		mciOpenParms.lpstrElementName = lpszWAVEFileName;
		mciOpenParms.lpstrAlias = alias;
		if (dwReturn = mciSendCommand(0, MCI_OPEN,
		MCI_OPEN_TYPE | MCI_OPEN_ELEMENT | MCI_OPEN_ALIAS, 
		(DWORD)(LPVOID) &mciOpenParms))
		{
			// Failed to open device. Don't close it; just return error.
			return (dwReturn);
		}
		// The device opened successfully; get the device ID.
		wDeviceID = mciOpenParms.wDeviceID;
	}
	{
		UINT num;
		DWORD vol;
		num = waveOutGetNumDevs();
		if(num)
			auxGetVolume(0, &vol);
		num;
	}

    // Begin playback. The window procedure function for the parent 
    // window will be notified with an MM_MCINOTIFY message when 
    // playback is complete. At this time, the window procedure closes 
    // the device.

    mciPlayParms.dwCallback = (DWORD) hwStopper;
    if (dwReturn = mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, 
        (DWORD)(LPVOID) &mciPlayParms))
    {
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    }

    return (0L);
}