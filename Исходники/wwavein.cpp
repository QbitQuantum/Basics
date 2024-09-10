void CALLBACK WWaveIn::_WaveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,DWORD dwParam1, DWORD dwParam2)
{
	WWaveIn *instance = (WWaveIn*) dwInstance;
	
 	switch(uMsg)
	{
	
    	case MM_WIM_OPEN:
        break;

        case MM_WIM_CLOSE:
        break;
		

        case MM_WIM_DATA:
		{
			if(instance->c_fWorking == 0)
				break;

			// add data to queue
			WAVEHDR* header = (WAVEHDR *) dwParam1;
			unsigned int nHaveRecorded = header->dwBytesRecorded;
			

			EnterCriticalSection(&instance->cs);
			// add new data to buffer
			if(nHaveRecorded)
				instance->c_Queue.PushLast(header->lpData, nHaveRecorded);

			unsigned int nHaveInQueue = instance->c_Queue.GetSizeSum();

			if(nHaveInQueue > instance->c_nMaxQueueSizeInBytes)
			{
				// need to cut
				instance->c_Queue.CutDataFifo(nHaveInQueue - instance->c_nMaxQueueSizeInBytes);
			}

			LeaveCriticalSection(&instance->cs);

		
			waveInUnprepareHeader(hwi, header, sizeof(WAVEHDR));
			header->dwFlags = 0;
			waveInPrepareHeader(hwi, header, sizeof(WAVEHDR));
			waveInAddBuffer(hwi, header, sizeof(WAVEHDR));
		



		}
        break;
    }
}