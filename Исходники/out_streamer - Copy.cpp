int Plugin_Open(int samplerate, int numchannels, int bitspersamp, int bufferlenms, int prebufferms)
{
	start_t = GetTickCount();
	w_offset = 0;
	writtenbytes = 0;
	numchan = numchannels;
	srate = samplerate;
	bps = bitspersamp;

	PrebufferBytesCount = ConvertMilisecondsToBytesCount(PrebufferTime);
	
	//forwarder->SetOutputDelay(BytesPerSecondCount);// 1 second
	forwarder->Open(samplerate, numchannels, bitspersamp, bufferlenms, prebufferms);
	outputStream->Initialize(samplerate, numchannels, bitspersamp);

	streamManager->open();	//mpdClient->play();

	return 0;
}