		// Choose an audio capture format using ACM
		void CAudioGrabber::ChooseAudioFormat()
		{
			DWORD dwSize;
			LPWAVEFORMATEX lpwfx;
			AM_MEDIA_TYPE *pmt;

			// There's no point if we can't set a new format
			if(pASC == NULL)
				return;

			// What's the largest format size around?
			acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize);
			HRESULT hr = pASC->GetFormat(&pmt);
			if(hr != NOERROR)
				return;

			lpwfx = (LPWAVEFORMATEX)pmt->pbFormat;
			dwSize = (DWORD) (max(dwSize, lpwfx->cbSize + sizeof(WAVEFORMATEX)));

			// !!! This doesn't really map to the supported formats of the filter.
			// We should be using a property page based on IAMStreamConfig

			lpwfx = (LPWAVEFORMATEX)GlobalAllocPtr(GHND, dwSize);
			if(lpwfx)
			{
				CopyMemory(lpwfx, pmt->pbFormat, pmt->cbFormat);

				lpwfx->nChannels = 1;
				lpwfx->nSamplesPerSec = 44100;
				lpwfx->wBitsPerSample = 16;
				lpwfx->nBlockAlign = lpwfx->nChannels * lpwfx->wBitsPerSample / 8;
				lpwfx->nAvgBytesPerSec = lpwfx->nChannels * lpwfx->nSamplesPerSec * lpwfx->wBitsPerSample / 8;
				//lpwfx->wFormatTag = 0x0161;
				

				((CMediaType *)pmt)->SetFormat((LPBYTE)lpwfx, lpwfx->cbSize + sizeof(WAVEFORMATEX));

				pASC->SetFormat(pmt);  // Filter will reconnect

				GlobalFreePtr(lpwfx) ;
			}
			DeleteMediaType(pmt);
		}