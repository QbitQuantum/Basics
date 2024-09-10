BOOL ClSoundDS::AddSoundBuffer(int handle,char *fileBuf,BOOL b3DSound)
{
	HRESULT			hr;
	RiffHead		riffHead;
	FmtHead			fmtHead;
	PCMWAVEFORMAT	pcmFormat;

	LPBYTE			lpBlockAdd1, lpBlockAdd2;
	DWORD			blockSize1, blockSize2;

	CopyMemory(&riffHead,fileBuf,sizeof(RiffHead));
	fileBuf += sizeof(RiffHead);
	if(strncmp(riffHead.riff,"RIFF",4) || strncmp(riffHead.type,"WAVE",4)){
		return FALSE;
	}
	if(NULL==lpDSBufferTop){
		lpDSBufferTop = lpDSBufferTail = new ClSoundBuffer;
	}else{
		lpDSBufferTail->lpNext = new ClSoundBuffer;
		lpDSBufferTail->lpNext->lpPrev = lpDSBufferTail;
		lpDSBufferTail = lpDSBufferTail->lpNext;
	}
	lpDSBufferTail->bufType = memory_sound;
	CopyMemory(&fmtHead,fileBuf,sizeof(FmtHead));
	fileBuf += sizeof(FmtHead);
	CopyMemory(&pcmFormat,fileBuf,sizeof(PCMWAVEFORMAT));
	if(pcmFormat.wf.wFormatTag == WAVE_FORMAT_PCM){
		fileBuf += fmtHead.size;
		CopyMemory(&fmtHead,fileBuf,sizeof(FmtHead));
		fileBuf += sizeof(FmtHead);
		while(0!=strncmp(fmtHead.fmt,"data",4)){
			fileBuf += fmtHead.size;
			CopyMemory(&fmtHead,fileBuf,sizeof(FmtHead));
			fileBuf += sizeof(FmtHead);
		}
		DSBUFFERDESC	dsbdesc;
		WAVEFORMATEX	audioFmt;
		ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		dsbdesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS;
		if(b3DSound) dsbdesc.dwFlags |= (DSBCAPS_CTRL3D | DSBCAPS_MUTE3DATMAXDISTANCE);
		dsbdesc.dwBufferBytes = fmtHead.size;
		CopyMemory(&audioFmt,&pcmFormat,sizeof(WAVEFORMAT));
		audioFmt.wBitsPerSample = pcmFormat.wBitsPerSample;
		audioFmt.cbSize = 0;
		dsbdesc.lpwfxFormat = &audioFmt;
		hr = lpDSound->CreateSoundBuffer(&dsbdesc, &lpTmpBuffer, NULL);
		lpTmpBuffer->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID *)&lpDSBufferTail->lpDSBuffer);
		RELEASE(lpTmpBuffer);
		hr = lpDSBufferTail->lpDSBuffer->Lock(0,fmtHead.size, (LPVOID*)&lpBlockAdd1, &blockSize1,(LPVOID*)&lpBlockAdd2, &blockSize2, 0);
		if(DS_OK==hr){
			CopyMemory(lpBlockAdd1,fileBuf,blockSize1);
			if(fmtHead.size>blockSize1){
				CopyMemory(lpBlockAdd2,fileBuf+blockSize1,blockSize2);
			}
			lpDSBufferTail->lpDSBuffer->Unlock(lpBlockAdd1, blockSize1, lpBlockAdd2, blockSize2);
		}
		lpDSBufferTail->handle = handle;
	}else{
		WAVEFORMATEX	dstWF;
		WAVEFORMATEX	*pwfxInfo;
		WORD			cbExtraAlloc;
		MMRESULT		mmResult;
		fileBuf += sizeof(PCMWAVEFORMAT);
		CopyMemory(&cbExtraAlloc,fileBuf,sizeof(WORD));
		fileBuf += sizeof(WORD);
		pwfxInfo = (WAVEFORMATEX *)cl_malloc(sizeof(WAVEFORMATEX) +cbExtraAlloc);
		CopyMemory(pwfxInfo,&pcmFormat,sizeof(PCMWAVEFORMAT));
		pwfxInfo->cbSize = cbExtraAlloc;
		CopyMemory((char *)pwfxInfo +sizeof(WAVEFORMATEX),fileBuf,cbExtraAlloc);
		fileBuf += (fmtHead.size -sizeof(WAVEFORMATEX));
		CopyMemory(&fmtHead,fileBuf,sizeof(FmtHead));
		fileBuf += sizeof(FmtHead);
		while(0!=strncmp(fmtHead.fmt,"data",4)){
			fileBuf += fmtHead.size;
			CopyMemory(&fmtHead,fileBuf,sizeof(FmtHead));
			fileBuf += sizeof(FmtHead);
		}
		ZeroMemory(&dstWF,sizeof(dstWF));
		dstWF.wFormatTag = WAVE_FORMAT_PCM;
		mmResult = acmFormatSuggest(
			NULL,
			pwfxInfo,
			&dstWF,
			sizeof(dstWF),
			ACM_FORMATSUGGESTF_WFORMATTAG);
		if(mmResult != 0){
			myOutputDebugString("オーディオ圧縮が無効です\n");
			return FALSE;
		}
		HACMSTREAM				hAcm = NULL;
		ACMSTREAMHEADER			ash;
		AcmBuffer				acmDst;
		AcmBuffer				acmSrc;

		acmStreamOpen(&hAcm, NULL,pwfxInfo,&dstWF, NULL, 0L, 0L, ACM_STREAMOPENF_NONREALTIME);
		acmSrc.dwStreamSize = fmtHead.size;
		acmStreamSize(hAcm, acmSrc.dwStreamSize, &acmDst.dwStreamSize, ACM_STREAMSIZEF_SOURCE);
		cl_free(pwfxInfo);
		acmSrc.lpStream = (LPBYTE)cl_malloc(acmSrc.dwStreamSize);
		acmDst.lpStream = (LPBYTE)cl_malloc(acmDst.dwStreamSize);
		ZeroMemory(&ash,sizeof(ash));
		ash.cbStruct		= sizeof(ash);
		ash.pbSrc			= acmSrc.lpStream;
		ash.cbSrcLength		= acmSrc.dwStreamSize;
		ash.dwSrcUser		= acmSrc.dwStreamSize;
		ash.pbDst			= acmDst.lpStream;
		ash.cbDstLength		= acmDst.dwStreamSize;
		ash.dwDstUser		= acmDst.dwStreamSize;
		acmStreamPrepareHeader(hAcm,&ash,0);
		CopyMemory(acmSrc.lpStream,fileBuf,acmSrc.dwStreamSize);
		MMRESULT nError = acmStreamConvert(hAcm,&ash, ACM_STREAMCONVERTF_BLOCKALIGN);
		DSBUFFERDESC	dsbdesc;
		ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		dsbdesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS;
		if(b3DSound) dsbdesc.dwFlags |= (DSBCAPS_CTRL3D | DSBCAPS_MUTE3DATMAXDISTANCE);
		dsbdesc.dwBufferBytes = ash.cbDstLengthUsed;
		dsbdesc.lpwfxFormat = &dstWF;
		hr = lpDSound->CreateSoundBuffer(&dsbdesc, &lpTmpBuffer, NULL);
		lpTmpBuffer->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID *)&lpDSBufferTail->lpDSBuffer);
		RELEASE(lpTmpBuffer);
		hr = lpDSBufferTail->lpDSBuffer->Lock(0,ash.cbDstLengthUsed, (LPVOID*)&lpBlockAdd1, &blockSize1,(LPVOID*)&lpBlockAdd2, &blockSize2, 0);
		if(DS_OK==hr){
			if(ash.cbDstLengthUsed < blockSize1){
				CopyMemory(lpBlockAdd1, acmDst.lpStream, ash.cbDstLengthUsed);
				ZeroMemory(lpBlockAdd1 +ash.cbDstLengthUsed, blockSize1 -ash.cbDstLengthUsed);
				if(blockSize2)ZeroMemory(lpBlockAdd2,blockSize2);
			}else{
				CopyMemory(lpBlockAdd1, acmDst.lpStream, blockSize1);
				if(blockSize2){
					CopyMemory(lpBlockAdd2, acmDst.lpStream+blockSize1, ash.cbDstLengthUsed -blockSize1);
				}
			}
			lpDSBufferTail->lpDSBuffer->Unlock(lpBlockAdd1, blockSize1, lpBlockAdd2, blockSize2);
		}
		if(hAcm){
			acmStreamUnprepareHeader(hAcm,&ash,0);
			acmStreamClose(hAcm,0);
			cl_free(acmSrc.lpStream);
			cl_free(acmDst.lpStream);
		}
		lpDSBufferTail->handle = handle;
	}
	return TRUE;
} // ClSoundDS::AddSoundBuffer