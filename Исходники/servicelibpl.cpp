eServiceMP3::eServiceMP3(eServiceReference ref):
	m_nownext_timer(eTimer::create(eApp)),
	m_cuesheet_changed(0),
	m_cutlist_enabled(1),
	m_ref(ref),
	m_pump(eApp, 1)
{
	eDebug("[eServiceMP3::%s]", __func__);
	m_currentAudioStream = -1;
	m_currentSubtitleStream = -1;
	m_cachedSubtitleStream = -1; /* report the first subtitle stream to be 'cached'. TODO: use an actual cache. */
	m_subtitle_widget = 0;
	m_buffer_size = 5 * 1024 * 1024;
	m_cuesheet_loaded = false; /* cuesheet CVR */
	inst_m_pump = &m_pump;
	CONNECT(m_nownext_timer->timeout, eServiceMP3::updateEpgCacheNowNext);
	CONNECT(inst_m_pump->recv_msg, eServiceMP3::gotThreadMessage);
	m_aspect = m_width = m_height = m_framerate = m_progressive = -1;
	m_state = stIdle;
	instance = this;

	player = (Context_t*) malloc(sizeof(Context_t));

	if (player)
	{
		player->playback  = &PlaybackHandler;
		player->output    = &OutputHandler;
		player->container = &ContainerHandler;
		player->manager   = &ManagerHandler;
		eDebug("[eServiceMP3::%s] %s", __func__, player->output->Name);
	}

	//Registration of output devices
	if (player && player->output)
	{
		player->output->Command(player,OUTPUT_ADD, (void*)"audio");
		player->output->Command(player,OUTPUT_ADD, (void*)"video");
		player->output->Command(player,OUTPUT_ADD, (void*)"subtitle");
	}

	if (player && player->output && player->output->subtitle)
	{
		fbClass *fb = fbClass::getInstance();
		SubtitleOutputDef_t out;
		out.screen_width = fb->getScreenResX();
		out.screen_height = fb->getScreenResY();
		out.shareFramebuffer = 1;
		out.framebufferFD = fb->getFD();
		out.destination = fb->getLFB_Direct();
		out.destStride = fb->Stride();
		out.framebufferBlit = ep3Blit;
		player->output->subtitle->Command(player, (OutputCmd_t)OUTPUT_SET_SUBTITLE_OUTPUT, (void*) &out);
	}

	//create playback path
	char file[1023] = {""};
	if ((!strncmp("http://", m_ref.path.c_str(), 7))
	|| (!strncmp("https://", m_ref.path.c_str(), 8))
	|| (!strncmp("cache://", m_ref.path.c_str(), 8))
	|| (!strncmp("concat://", m_ref.path.c_str(), 9))
	|| (!strncmp("crypto://", m_ref.path.c_str(), 9))
	|| (!strncmp("gopher://", m_ref.path.c_str(), 9))
	|| (!strncmp("hls://", m_ref.path.c_str(), 6))
	|| (!strncmp("hls+http://", m_ref.path.c_str(), 11))
	|| (!strncmp("httpproxy://", m_ref.path.c_str(), 12))
	|| (!strncmp("mmsh://", m_ref.path.c_str(), 7))
	|| (!strncmp("mmst://", m_ref.path.c_str(), 7))
	|| (!strncmp("rtmp://", m_ref.path.c_str(), 7))
	|| (!strncmp("rtmpe://", m_ref.path.c_str(), 8))
	|| (!strncmp("rtmpt://", m_ref.path.c_str(), 8))
	|| (!strncmp("rtmps://", m_ref.path.c_str(), 8))
	|| (!strncmp("rtmpte://", m_ref.path.c_str(), 9))
	|| (!strncmp("ftp://", m_ref.path.c_str(), 6))
	|| (!strncmp("rtp://", m_ref.path.c_str(), 6))
	|| (!strncmp("srtp://", m_ref.path.c_str(), 7))
	|| (!strncmp("subfile://", m_ref.path.c_str(), 10))
	|| (!strncmp("tcp://", m_ref.path.c_str(), 6))
	|| (!strncmp("tls://", m_ref.path.c_str(), 6))
	|| (!strncmp("udp://", m_ref.path.c_str(), 6))
	|| (!strncmp("udplite://", m_ref.path.c_str(), 10)))
		m_sourceinfo.is_streaming = true;
	else if ((!strncmp("file://", m_ref.path.c_str(), 7))
	|| (!strncmp("bluray://", m_ref.path.c_str(), 9))
	|| (!strncmp("hls+file://", m_ref.path.c_str(), 11))
	|| (!strncmp("myts://", m_ref.path.c_str(), 7)))
		;
	else
		strcat(file, "file://");

	strcat(file, m_ref.path.c_str());

	//try to open file
	if (player && player->playback && player->playback->Command(player, PLAYBACK_OPEN, file) >= 0)
	{
		//VIDEO
		//We dont have to register video tracks, or do we ?
		//AUDIO
		if (player && player->manager && player->manager->audio)
		{
			char ** TrackList = NULL;
			player->manager->audio->Command(player, MANAGER_LIST, &TrackList);
			if (TrackList != NULL)
			{
				eDebug("[eServiceMP3::%s] AudioTrack List:", __func__);
				int i = 0;
				for (i = 0; TrackList[i] != NULL; i+=2)
				{
					eDebug("[eServiceMP3::%s]\t%s - %s", __func__, TrackList[i], TrackList[i+1]);
					audioStream audio;
					audio.language_code = TrackList[i];

					// atUnknown, atMPEG, atMP3, atAC3, atDTS, atAAC, atPCM, atOGG, atFLAC
					if (    !strncmp("A_MPEG/L3",   TrackList[i+1], 9))
						audio.type = atMP3;
					else if (!strncmp("A_MP3",      TrackList[i+1], 5))
						audio.type = atMP3;
					else if (!strncmp("A_AC3",      TrackList[i+1], 5))
						audio.type = atAC3;
					else if (!strncmp("A_DTS",      TrackList[i+1], 5))
						audio.type = atDTS;
					else if (!strncmp("A_AAC",      TrackList[i+1], 5))
						audio.type = atAAC;
					else if (!strncmp("A_PCM",      TrackList[i+1], 5))
						audio.type = atPCM;
					else if (!strncmp("A_VORBIS",   TrackList[i+1], 8))
						audio.type = atOGG;
					else if (!strncmp("A_FLAC",     TrackList[i+1], 6))
						audio.type = atFLAC;
					else
						audio.type = atUnknown;

					m_audioStreams.push_back(audio);
					free(TrackList[i]);
					TrackList[i] = NULL;
					free(TrackList[i+1]);
					TrackList[i+1] = NULL;
				}
				free(TrackList);
				TrackList = NULL;
			}
		}

		//SUB
		if (player && player->manager && player->manager->subtitle)
		{
			char ** TrackList = NULL;
			player->manager->subtitle->Command(player, MANAGER_LIST, &TrackList);
			if (TrackList != NULL)
			{
				eDebug("[eServiceMP3::%s] SubtitleTrack List:", __func__);
				int i = 0;
				for (i = 0; TrackList[i] != NULL; i+=2)
				{
					eDebug("[eServiceMP3::%s]\t%s - %s", __func__, TrackList[i], TrackList[i+1]);
					subtitleStream sub;
					sub.language_code = TrackList[i];

					//  stPlainText, stSSA, stSRT
					if (     !strncmp("S_TEXT/SSA",   TrackList[i+1], 10) ||
							!strncmp("S_SSA", TrackList[i+1], 5))
						sub.type = stSSA;
					else if (!strncmp("S_TEXT/ASS",   TrackList[i+1], 10) ||
							!strncmp("S_AAS", TrackList[i+1], 5))
						sub.type = stSSA;
					else if (!strncmp("S_TEXT/SRT",   TrackList[i+1], 10) ||
							!strncmp("S_SRT", TrackList[i+1], 5))
						sub.type = stSRT;
					else
						sub.type = stPlainText;

					m_subtitleStreams.push_back(sub);
					free(TrackList[i]);
					TrackList[i] = NULL;
					free(TrackList[i+1]);
					TrackList[i+1] = NULL;
				}
				free(TrackList);
				TrackList = NULL;
			}
		}
		loadCuesheet(); /* cuesheet CVR */
		m_event(this, evStart);
	}
	else
	{
		//Creation failed, no playback support for insert file, so send e2 EOF to stop playback
		eDebug("[eServiceMP3::%s] ERROR! Creation failed! No playback support for insert file!", __func__);
		m_state = stRunning;
		m_event(this, evEOF);
	}
}