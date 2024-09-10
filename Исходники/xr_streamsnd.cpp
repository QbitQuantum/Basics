//--------------------------------------------------------------------------------------------------
BOOL CSoundStream::Decompress(unsigned char *dest)
{
    u32				dwSrcSize = dwSrcBufSize;
	BOOL				r = true;

	VERIFY				(hAcmStream);

	// check for EOF
    if (dwDecPos+dwSrcSize>dwTotalSize) {
		dwSrcSize=dwTotalSize-dwDecPos;
		r=false;
	}
	hf->r	(WaveSource,dwSrcSize);

    stream.cbStruct=sizeof(stream);
    stream.fdwStatus=0;
    stream.pbSrc=WaveSource;
    stream.cbSrcLength=dwSrcSize;
    stream.pbDst=dest;
    stream.cbDstLength=dwDestBufSize;

	CHK_DX(acmStreamPrepareHeader(hAcmStream,&stream,0));
    CHK_DX(acmStreamConvert(hAcmStream,&stream,0));
    CHK_DX(acmStreamUnprepareHeader(hAcmStream,&stream,0));
    dwDecPos+=stream.cbSrcLengthUsed;

	AppWriteDataToBuffer(writepos,WaveDest,stream.cbDstLengthUsed);

    return r;
}