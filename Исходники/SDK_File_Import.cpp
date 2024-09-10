/* 
	Populate the imFileInfoRec8 structure describing this file instance
	to Premiere.  Check file validity, allocate any private instance data 
	to share between different calls.
*/
prMALError 
SDKGetInfo8(
	imStdParms			*stdParms, 
	imFileAccessRec8	*fileAccessInfo, 
	imFileInfoRec8		*fileInfo)
{
	prMALError					result				= malNoError;
	PrivateDataH pdH = reinterpret_cast<PrivateDataH>(fileInfo->privatedata); 

	stdParms->piSuites->memFuncs->lockHandle(reinterpret_cast<char**>(pdH)); //Lock private data

	(*pdH)->flacErrorCode = 0;
	(*pdH)->flacDecoder = 0;

	char filepathASCII[255];
	int stringLength = (int)wcslen(reinterpret_cast<const wchar_t*>(fileAccessInfo->filepath));
	wcstombs_s(	NULL, reinterpret_cast<char*>(filepathASCII), sizeof (filepathASCII), fileAccessInfo->filepath, stringLength);

	FLAC__bool ok = true;
    FLAC__StreamDecoderInitStatus init_status;
	if(((*pdH)->flacDecoder = FLAC__stream_decoder_new()) == NULL)
	{
		(*pdH)->flacErrorCode = 1;
	}

	FLAC__stream_decoder_set_md5_checking((*pdH)->flacDecoder, true);

	init_status = FLAC__stream_decoder_init_file((*pdH)->flacDecoder, filepathASCII, write_callback, NULL, error_callback, pdH);
	if(init_status != FLAC__STREAM_DECODER_INIT_STATUS_OK )
	{
		return imBadFile; //Error, bail out
	}
	FLAC__stream_decoder_process_until_end_of_metadata((*pdH)->flacDecoder);
	FLAC__stream_decoder_process_single((*pdH)->flacDecoder);

	(*pdH)->audioChannels = FLAC__stream_decoder_get_channels((*pdH)->flacDecoder);
	(*pdH)->audioNumberOfSamples = FLAC__stream_decoder_get_total_samples((*pdH)->flacDecoder);
	(*pdH)->audioNumberOfSamplesPerSecond = FLAC__stream_decoder_get_sample_rate((*pdH)->flacDecoder);
	(*pdH)->audioBytesPerSample = FLAC__stream_decoder_get_bits_per_sample((*pdH)->flacDecoder) / 8;
	(*pdH)->audioPosition = 0;

	//Fill out the general file info
	fileInfo->accessModes						= kSeparateSequentialAudio;
	fileInfo->hasDataRate						= kPrFalse;	
	fileInfo->hasVideo							= kPrFalse;
	fileInfo->hasAudio							= kPrTrue;
	fileInfo->alwaysUnquiet						= 0;
	fileInfo->highMemUsage						= 0;
	fileInfo->audInfo.numChannels				= (*pdH)->audioChannels;
	fileInfo->audInfo.sampleRate				= (float)(*pdH)->audioNumberOfSamplesPerSecond;
	fileInfo->audDuration						= (*pdH)->audioNumberOfSamples;

	if((*pdH)->audioBytesPerSample == 1)
	{
		fileInfo->audInfo.sampleType = kPrAudioSampleType_8BitInt;
	}
	else if((*pdH)->audioBytesPerSample == 2)
	{
		fileInfo->audInfo.sampleType = kPrAudioSampleType_16BitInt;
	}
	else if((*pdH)->audioBytesPerSample == 3)
	{
		fileInfo->audInfo.sampleType = kPrAudioSampleType_24BitInt;
	}
	else if((*pdH)->audioBytesPerSample == 4)
	{
		fileInfo->audInfo.sampleType = kPrAudioSampleType_32BitInt;
	}
	else
	{
		fileInfo->audInfo.sampleType = kPrAudioSampleType_Other;
	}

	(*pdH)->suiteBasic = stdParms->piSuites->utilFuncs->getSPBasicSuite(); //Allocate an audio suite
	if ((*pdH)->suiteBasic)
	{
		(*pdH)->suiteBasic->AcquireSuite (kPrSDKAudioSuite, kPrSDKAudioSuiteVersion, (const void**)&(*pdH)->suiteAudio);
	}

	stdParms->piSuites->memFuncs->unlockHandle(reinterpret_cast<char**>(pdH)); //Unlock private data

	return result;
}