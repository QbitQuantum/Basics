void cinderFFmpegApp::setup()
{
	m_Font = ci::Font("Consolas", 48);
	setupGui();
	gl::enableAlphaBlending();

	std::shared_ptr<_2RealFFmpegWrapper::FFmpegWrapper> testFile = std::shared_ptr<_2RealFFmpegWrapper::FFmpegWrapper>(new _2RealFFmpegWrapper::FFmpegWrapper());
	testFile->dumpFFmpegInfo();
	//if(testFile->open(".\\data\\morph.avi"))
	if(testFile->open("d:\\vjing\\Wildlife.wmv"))
	{
		m_Players.push_back(testFile);
		m_VideoTextures.push_back(gl::Texture());
		m_Players.back()->play();
	}

	m_dLastTime = 0;
	m_iCurrentVideo = 0;
	m_fSpeed = 1;
	m_iLoopMode = _2RealFFmpegWrapper::eLoop;
	m_iTilesDivisor = 1;
	m_fSeekPos = m_fOldSeekPos = 0;

	//setup fmod
	FMOD::System_Create(&m_pSystem);
    m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
   
	memset(&createsoundexinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    createsoundexinfo.cbsize            = sizeof(FMOD_CREATESOUNDEXINFO);              /* required. */
    createsoundexinfo.decodebuffersize  = 1024;                                       /* Chunk size of stream update in samples.  This will be the amount of data passed to the user callback. */
    createsoundexinfo.numchannels       = 2;                        /* Number of channels in the sound. */
    createsoundexinfo.length            = -1;                     /* Length of PCM data in bytes of whole song.  -1 = infinite. */
    createsoundexinfo.defaultfrequency  = (int)44100;                       /* Default playback rate of sound. */
	createsoundexinfo.format            = FMOD_SOUND_FORMAT_PCM16;                    /* Data format of sound. */
	createsoundexinfo.pcmreadcallback   =  pcmreadcallback;                             /* User callback for reading. */

	result = m_pSystem->createStream(0, FMOD_2D | FMOD_OPENUSER | FMOD_LOOP_OFF, &createsoundexinfo, &m_pSound);
	result = m_pSystem->playSound(FMOD_CHANNEL_FREE, m_pSound, 0, &m_pChannel);

	//std::shared_ptr<audio::Callback<cinderFFmpegApp,unsigned short>> audioCallback = audio::createCallback( this, &cinderFFmpegApp::audioCallback );
	//audio::Output::play( audioCallback );
}