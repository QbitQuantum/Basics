void eDVRPlayerThread::init_eDVRPlayerThread(const char *_filename)
{
	state=stateInit;
	int nodetect=0;
	eConfig::getInstance()->getKey("/enigma/notimestampdetect", nodetect );
	timestampParser = nodetect ? 0 : new eTimeStampParserTS(_filename);
		

	int count=0;
	seekbusy=0;
	seeking=0;
#if HAVE_DVB_API_VERSION < 3
	do
	{
		dvrfd=::open("/dev/pvr", O_WRONLY|O_NONBLOCK); // TODO: change to /dev/dvb/dvr0 (but only when drivers support this!)
		if (dvrfd < 0)
		{
			if ( errno == EBUSY )
			{
				eDebug("pvr device busy try %d", count++);
				if ( count < 40 )
				{
					usleep(20000);
					continue;
				}
			}
			eDebug("couldn't open /dev/pvr - buy the new $$$ box and load pvr.o! (%m)");
			state=stateError;
		}
		break;
	}
	while( dvrfd < 0 );
#else
	if ((dvrfd = ::open("/dev/dvb/adapter0/dvr0", O_WRONLY|O_NONBLOCK)) == -1) 
	{
		eDebug("couldn't open /dev/dvb/adapter0/dvr0 (%m)");
		state=stateError;
	}
#endif
	outputsn=new eSocketNotifier(this, dvrfd, eSocketNotifier::Write, 0);
	CONNECT(outputsn->activated, eDVRPlayerThread::outputReady);

	CONNECT(liveupdatetimer.timeout, eDVRPlayerThread::updatePosition);

	filename=_filename;

	sourcefd=-1;
	inputsn=0;

	slice=0;
	audiotracks=1;

	if (playingPermanentTimeshift)
	{
		filelength = permanentTimeshift.getCurrentLength (-1)/1880;
	}
	else
	{
		filelength = FillSliceSizes();
	}

	if (openFile(0))
	{
		state=stateError;
		eDebug("error opening %s (%m)", filename.c_str());
	}

	CONNECT(messages.recv_msg, eDVRPlayerThread::gotMessage);

	if ( eSystemInfo::getInstance()->getHwType() < 3 ) // dbox2
		maxBufferFullness=128*1024;
	else
		maxBufferFullness=256*1024;

	speed=1;

	run();

	if (livemode)
	{
		int fileend;
		if (filelength > (TIMESHIFT_GUARD/1880))
			fileend = filelength - (TIMESHIFT_GUARD/1880);
		else
			fileend = 0;
		if ( livemode == 1 )
			messages.send(eDVRPlayerThread::eDVRPlayerThreadMessage(eDVRPlayerThread::eDVRPlayerThreadMessage::seekreal, fileend));
	}

	FILE *bitstream=fopen("/proc/bus/bitstream", "rt");
	if (bitstream)
	{
		char buf[100];
		while (fgets(buf, 100, bitstream))
		{
			if (strstr(buf, "AUDIO_STC:"))
			{
				needasyncworkaround=1;
				break;
			}
		}
		fclose(bitstream);
	}
}