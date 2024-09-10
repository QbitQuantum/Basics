/*-----------------------------------------------------------------------------
--	FUNCTION:		receiveStream
--
--	DATE:			2009-04-06
--
--	REVISIONS:		2009-04-06 - Jaymz, Took out the TCP connection stuff since
--								 we already have that at this point. Also added
--								 a parameter WPARAM sd, which is the socket
--								 from which we are receiving the data.
--							   - Jaymz, Miscellaneous code touch-ups (mainly
--								 formatting and removing of test printf()'s)
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Jaymz Boilard, Steffen L. Norgren
--
--	INTERFACE:		receiveStream(LPVOID iValue)
--
--	RETURNS:		void
--
--	NOTES: The main function to receive a UDP stream of data and process
--	that information.
-----------------------------------------------------------------------------*/
DWORD WINAPI receiveStream(LPVOID iValue)
{
	WAVEFORMATEX	wfx;
	char			buffer[BLOCK_SIZE]; /* intermediate buffer for reading */
	int				i, n, remote_len;
	DWORD			outBytes = 0;
	char			* play_byte = "1";
	BOOL			firstRun = TRUE;

	remote_len = sizeof(udp_remote);

	/* initialise the module variables */
	waveBlocks			= allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	waveFreeBlockCount	= BLOCK_COUNT;
	waveCurrentBlock	= 0;
	InitializeCriticalSection(&waveCriticalSection);
	
	/* playback loop - read from socket */
	while (TRUE) 
	{
		if (ci.request != MULTI_STREAM) {
			/* send play signal */
			sendto(ci.udpSocket, play_byte, sizeof(play_byte), 0, (struct sockaddr *)&udp_remote, remote_len);
		}

		if ((n = recvfrom(ci.udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&udp_remote, &remote_len)) <= 0)
		{
			waveOutClose(hWaveOut);
			ExitThread(0);
		}

		/* first 4 bytes in a file, so set the header information */
		if(strncmp(buffer, "RIFF", 4) == 0)
		{
			memcpy(&wfx, buffer+20, sizeof(wfx));

			if (ci.request != MULTI_STREAM || firstRun == TRUE) {
				waveOutClose(hWaveOut);
			
				if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc,
					(DWORD_PTR)&waveFreeBlockCount, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
				{
						MessageBox(NULL, "Unable to open mapper device.", "Error", MB_OK);
						ExitProcess(1);
				}
				firstRun = FALSE;
			}
		}

		if(n == 0)
			break;
		else if(n < sizeof(buffer) && n != WAVE_HEAD_SIZE)
		{
			memset(buffer + n, 0, sizeof(buffer) - n);
			writeAudio(buffer, n);
			break;
		}

		writeAudio(buffer, n);
	}

	/* wait for all blocks to complete */
	while(waveFreeBlockCount < BLOCK_COUNT)
		Sleep(10);

	/* unprepare any blocks that are still prepared */
	for(i = 0; i < waveFreeBlockCount; i++)
	{
		if(waveBlocks[i].dwFlags & WHDR_PREPARED)
			waveOutUnprepareHeader(hWaveOut, &waveBlocks[i], sizeof(WAVEHDR));
	}
	DeleteCriticalSection(&waveCriticalSection);
	freeBlocks(waveBlocks);
	waveOutClose(hWaveOut);
	streamInProgress = FALSE;
	ExitThread(0);
}