::FLAC__StreamDecoderTellStatus
OurDecoder::tell_callback(FLAC__uint64 *absolute_byte_offset)
{
#ifdef PRWIN_ENV
	LARGE_INTEGER lpos, zero;

	zero.QuadPart = 0;

	BOOL result = SetFilePointerEx(_fp, zero, &lpos, FILE_CURRENT);

	*absolute_byte_offset = lpos.QuadPart;
	
	return (result ? FLAC__STREAM_DECODER_TELL_STATUS_OK : FLAC__STREAM_DECODER_TELL_STATUS_ERROR);
#else
	SInt64 lpos;

	OSErr result = FSGetForkPosition(CAST_REFNUM(_fp), &lpos);
	
	*absolute_byte_offset = lpos;
	
	return (result == noErr ? FLAC__STREAM_DECODER_TELL_STATUS_OK : FLAC__STREAM_DECODER_TELL_STATUS_ERROR);
#endif
}