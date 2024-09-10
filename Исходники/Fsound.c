/*
	[DESCRIPTION]

	[PARAMETERS]
 
	[RETURN_VALUE]

	[REMARKS]

	[SEE_ALSO]
*/
DWORD FSOUND_Software_DoubleBufferThread(LPDWORD lpdwParam)
{
	int totalblocks; 

	FSOUND_Software_ThreadFinished = FALSE;

	totalblocks = FSOUND_BufferSize / FSOUND_BlockSize; 

	while (!FSOUND_Software_Exit)
	{
		int		cursorpos,cursorblock,prevblock;
		MMTIME	mmt;

		mmt.wType = TIME_BYTES;
		waveOutGetPosition(FSOUND_WaveOutHandle, &mmt, sizeof(MMTIME));
		mmt.u.cb >>= 2;
		cursorpos = mmt.u.cb;

		cursorpos %= FSOUND_BufferSize;
		cursorblock = cursorpos / FSOUND_BlockSize;

		prevblock = cursorblock - 1;
		if (prevblock < 0)
			prevblock = totalblocks - 1;

		while (FSOUND_Software_FillBlock != cursorblock)
		{
			FSOUND_Software_UpdateMutex = TRUE;

			FSOUND_Software_Fill();
	
			FSOUND_Software_RealBlock++;
			if (FSOUND_Software_RealBlock >= totalblocks)
				FSOUND_Software_RealBlock = 0;

			FSOUND_Software_UpdateMutex = FALSE;
		}

		Sleep(5);
	};

	FSOUND_Software_ThreadFinished = TRUE;

	return 0;
}