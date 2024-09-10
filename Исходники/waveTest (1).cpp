void CALLBACK waveInProc(HWAVEIN hwi,      
						 UINT uMsg,         
						 DWORD_PTR dwInstance,  
						 DWORD_PTR dwParam1,  
						 DWORD_PTR dwParam2     )
{
	LPWAVEHDR pwh = (LPWAVEHDR)dwParam1;

	if ((WIM_DATA==uMsg) && (buf_count<BUFFER_SIZE))
	{

		int size = pwh->dwBytesRecorded;

		//relocated memory location
		pNewBuffer = (PBYTE)realloc (pSaveBuffer, dwDataLength+ size) ; 

		if(pNewBuffer ==NULL)
		{
			waveInClose(hwi);
			printf("memory error");
			return;
		}

		//copy data into memory and refresh memory address
		pSaveBuffer = pNewBuffer;
		buf_count ++;
		CopyMemory(pSaveBuffer + dwDataLength, pwh->lpData,size);
		dwDataLength += size;

		if(!m_record)
		{
			waveInClose(hwi);
			printf("stop recording");
			return;
		}		
		waveInAddBuffer(hwi, pwh, sizeof(WAVEHDR));
	}
}