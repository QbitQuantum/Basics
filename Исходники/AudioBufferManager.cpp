bool AudioBufferManager::processSrcData(
	const void** appSrcBuffer,
	CAUDIO_U32_t aSrcBufferLen,
	CAUDIO_U32_t aSrcDataSize,
	void** appOutBuffer,
	CAUDIO_U32_t aOutBufferLen)
{
	if(!mIsInitSuccess)
	{
		AUDIO_PROCESSING_PRINTF("init AudioBufferManager failed");
		return false;
	}

	if (NULL == appSrcBuffer)
	{
		AUDIO_PROCESSING_PRINTF("apSrcBuffer is NULL");
		return false;
	}

	if(mMode != AUDIO_BUFFER_MANAGER_MODE_PROCESS)
	{
		AUDIO_PROCESSING_PRINTF("this API is only for process mode");
		return false;
	}

	CAUDIO_U32_t srcDataLen = mLenOfSample * aSrcDataSize;

	// calculate processing rounds according to mFrameShiftLen
	CAUDIO_U32_t maxLoop = (srcDataLen + mpBufferCondition[0].mInDefBufferWritePtr) / mFrameShiftLen;
	for (CAUDIO_U32_t i = 0; i < maxLoop; i++)
	{
		if (!readFrameShiftDataFromSrcBuffer(appSrcBuffer, aSrcBufferLen, srcDataLen))
		{
			return false;
		}

		// call callback function
		if (!mAudioProcessor.processData(mppProcessBufferPtrs, mProcessBufferLen, mInChannelNum, mOutChannelNum))
		{
			AUDIO_PROCESSING_PRINTF("process data failed");
		}

		// copy data to post processed buffer as much as what is processed
		if (!writeToPostProcessBuffer())
		{
			return false;
		}
	}

	// copy data from post process buffer to out channel buffer for every out channel
	for (CAUDIO_U8_t channelIndex = 0; channelIndex < mOutChannelNum; channelIndex++)
	{
		void* pOutChannelBuf = *(appOutBuffer + channelIndex);
		memcpy_s(pOutChannelBuf, aOutBufferLen, (const CAUDIO_U8_t*)mpBufferCondition[channelIndex].mpPostProcessBuffer, srcDataLen);
		if (srcDataLen < mpBufferCondition[channelIndex].mPostProBufWrtPtr)
		{
			// move left data in post process buffer to the head of buffer
			memmove_s(mpBufferCondition[channelIndex].mpPostProcessBuffer, mPostProcessBufferLen, 
				(const CAUDIO_U8_t*)mpBufferCondition[channelIndex].mpPostProcessBuffer + srcDataLen, mpBufferCondition[channelIndex].mPostProBufWrtPtr - srcDataLen);
		}

		mpBufferCondition[channelIndex].mPostProBufWrtPtr -= srcDataLen;
	}

	// copy left source data from in channel buffer to in deficiency buffer
	// these data would be processed at next calling
	for (CAUDIO_U8_t channelIndex = 0; channelIndex < mInChannelNum; channelIndex++)
	{
		CAUDIO_U32_t srcDataLeft = srcDataLen - mpBufferCondition[channelIndex].mSrcBufferReadPtr;
		if (0 < srcDataLeft)
		{
			const void* pSrcChannelBuf = *(appSrcBuffer + channelIndex);
			memcpy_s((CAUDIO_U8_t *)mpBufferCondition[channelIndex].mpInDeficiencyBuffer + mpBufferCondition[channelIndex].mInDefBufferWritePtr, 
				mInDefBufferLen - mpBufferCondition[channelIndex].mInDefBufferWritePtr,
				(const CAUDIO_U8_t*)pSrcChannelBuf + mpBufferCondition[channelIndex].mSrcBufferReadPtr, 
				srcDataLeft);
			mpBufferCondition[channelIndex].mInDefBufferWritePtr += srcDataLeft;
		}

		mpBufferCondition[channelIndex].mSrcBufferReadPtr = 0;
	}

	return true;
}