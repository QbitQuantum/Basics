void CDebugRouterClient::RunL()
	{
	TUint chunkSize = iSharedChunk.Size();
	const TUint KDataStartOffset = sizeof(SDebugChunkHeader);
	SDebugChunkHeader* chunkHeader = (SDebugChunkHeader*)iSharedChunk.Base();
	TUint start = chunkHeader->iStartOffset;
	TUint end = chunkHeader->iEndOffset;
	TUint overflows = chunkHeader->iOverflows;

	TBool wrap = (start > end);
	TUint endLen = wrap ? chunkSize - start : end - start;
	TUint startLen = wrap ? end - KDataStartOffset : 0;

	TPtrC8 endData(iSharedChunk.Base() + start, endLen);
	TPtrC8 startData;
	if (wrap) startData.Set(iSharedChunk.Base() + KDataStartOffset, startLen);
	TPtrC8 data(endData);

	while (data.Length())
		{
		TPtrC8 header = Read(iTempBuf, data, sizeof(SCloggerTraceInfo), startData);
		if (header.Length() < (TInt)sizeof(SCloggerTraceInfo))
			{
			ASSERT(EFalse); // for udeb
			break; // Something's broken
			}
		SCloggerTraceInfo info;
		Mem::Copy(&info, header.Ptr(), sizeof(SCloggerTraceInfo));
		ASSERT(info.iTraceType == 'K' || info.iTraceType == 'U' || info.iTraceType == 'P');
		TPtrC8 msg = Read(iTempBuf, data, info.iLength, startData);
		iServer.LogKernMessage(info.iTraceType, info.iTickCount, info.iThreadId, msg);
		}
	if (overflows)
		{
		_LIT8(KErr, "RDebug::Print buffer overflowed, %u calls not logged");
		iServer.LogError(KErr, overflows);
		}
	// Zero the memory so it's easier to read in the crashlog
	memclr(iSharedChunk.Base() + start, endLen);
	if (startLen) memclr(iSharedChunk.Base() + KDataStartOffset, startLen);
	
	StartRouting(-1); // Magic number to indicate no need to call EnableDebugRouting again
	}