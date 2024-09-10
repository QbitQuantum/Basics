eServiceMP3::eServiceMP3(eServiceReference ref)
	:m_ref(ref), m_pump(eApp, 1)
{
	m_subtitle_sync_timer = eTimer::create(eApp);
	m_streamingsrc_timeout = 0;
	m_stream_tags = 0;
	m_currentAudioStream = -1;
	m_currentSubtitleStream = -1;
	m_subtitle_widget = 0;
	m_currentTrickRatio = 1.0;
	m_buffer_size = 1*1024*1024;
	m_prev_decoder_time = -1;
	m_decoder_time_valid_state = 0;
	m_errorInfo.missing_codec = "";

	CONNECT(m_subtitle_sync_timer->timeout, eServiceMP3::pushSubtitles);
	CONNECT(m_pump.recv_msg, eServiceMP3::gstPoll);
	m_aspect = m_width = m_height = m_framerate = m_progressive = -1;

	m_state = stIdle;
	eDebug("eServiceMP3::construct!");

	const char *filename = m_ref.path.c_str();
	const char *ext = strrchr(filename, '.');
	if (!ext)
		ext = filename;

	m_sourceinfo.is_video = FALSE;
	m_sourceinfo.audiotype = atUnknown;
	if ( (strcasecmp(ext, ".mpeg") && strcasecmp(ext, ".mpg") && strcasecmp(ext, ".vob") && strcasecmp(ext, ".bin") && strcasecmp(ext, ".dat") ) == 0 )
	{
		m_sourceinfo.containertype = ctMPEGPS;
		m_sourceinfo.is_video = TRUE;
	}
	else if ( strcasecmp(ext, ".ts") == 0 )
	{
		m_sourceinfo.containertype = ctMPEGTS;
		m_sourceinfo.is_video = TRUE;
	}
	else if ( strcasecmp(ext, ".mkv") == 0 )
	{
		m_sourceinfo.containertype = ctMKV;
		m_sourceinfo.is_video = TRUE;
	}
	else if ( strcasecmp(ext, ".avi") == 0 || strcasecmp(ext, ".divx") == 0)
	{
		m_sourceinfo.containertype = ctAVI;
		m_sourceinfo.is_video = TRUE;
	}
	else if ( strcasecmp(ext, ".mp4") == 0 || strcasecmp(ext, ".mov") == 0 || strcasecmp(ext, ".m4v") == 0)
	{
		m_sourceinfo.containertype = ctMP4;
		m_sourceinfo.is_video = TRUE;
	}
	else if ( strcasecmp(ext, ".m4a") == 0 )
	{
		m_sourceinfo.containertype = ctMP4;
		m_sourceinfo.audiotype = atAAC;
	}
	else if ( strcasecmp(ext, ".mp3") == 0 )
		m_sourceinfo.audiotype = atMP3;
	else if ( (strncmp(filename, "/autofs/", 8) || strncmp(filename+strlen(filename)-13, "/track-", 7) || strcasecmp(ext, ".wav")) == 0 )
		m_sourceinfo.containertype = ctCDA;
	if ( strcasecmp(ext, ".dat") == 0 )
	{
		m_sourceinfo.containertype = ctVCD;
		m_sourceinfo.is_video = TRUE;
	}
	if ( strstr(filename, "://") )
		m_sourceinfo.is_streaming = TRUE;

	gchar *uri;

	if ( m_sourceinfo.is_streaming )
	{
		uri = g_strdup_printf ("%s", filename);
		m_streamingsrc_timeout = eTimer::create(eApp);;
		CONNECT(m_streamingsrc_timeout->timeout, eServiceMP3::sourceTimeout);

		std::string config_str;
		if( ePythonConfigQuery::getConfigValue("config.mediaplayer.useAlternateUserAgent", config_str) == 0 )
		{
			if ( config_str == "True" )
				ePythonConfigQuery::getConfigValue("config.mediaplayer.alternateUserAgent", m_useragent);
		}
		if ( m_useragent.length() == 0 )
			m_useragent = "Dream Multimedia Dreambox Enigma2 Mediaplayer";
	}
	else if ( m_sourceinfo.containertype == ctCDA )
	{
		int i_track = atoi(filename+18);
		uri = g_strdup_printf ("cdda://%i", i_track);
	}
	else if ( m_sourceinfo.containertype == ctVCD )
	{
		int fd = open(filename,O_RDONLY);
		char tmp[128*1024];
		int ret = read(fd, tmp, 128*1024);
		close(fd);
		if ( ret == -1 ) // this is a "REAL" VCD
			uri = g_strdup_printf ("vcd://");
		else
			uri = g_filename_to_uri(filename, NULL, NULL);
	}
	else

		uri = g_filename_to_uri(filename, NULL, NULL);

	eDebug("eServiceMP3::playbin2 uri=%s", uri);

	m_gst_playbin = gst_element_factory_make("playbin2", "playbin");
	if (!m_gst_playbin)
		m_errorInfo.error_message = "failed to create GStreamer pipeline!\n";

	g_object_set (G_OBJECT (m_gst_playbin), "uri", uri, NULL);

	int flags = 0x47; // ( GST_PLAY_FLAG_VIDEO | GST_PLAY_FLAG_AUDIO | GST_PLAY_FLAG_NATIVE_VIDEO | GST_PLAY_FLAG_TEXT );
	g_object_set (G_OBJECT (m_gst_playbin), "flags", flags, NULL);

	g_free(uri);

	GstElement *subsink = gst_element_factory_make("subsink", "subtitle_sink");
	if (!subsink)
		eDebug("eServiceMP3::sorry, can't play: missing gst-plugin-subsink");
	else
	{
		m_subs_to_pull_handler_id = g_signal_connect (subsink, "new-buffer", G_CALLBACK (gstCBsubtitleAvail), this);
		g_object_set (G_OBJECT (subsink), "caps", gst_caps_from_string("text/plain; text/x-plain; text/x-pango-markup; video/x-dvd-subpicture; subpicture/x-pgs"), NULL);
		g_object_set (G_OBJECT (m_gst_playbin), "text-sink", subsink, NULL);
		g_object_set (G_OBJECT (m_gst_playbin), "current-text", m_currentSubtitleStream, NULL);
	}

	if ( m_gst_playbin )
	{
		gst_bus_set_sync_handler(gst_pipeline_get_bus (GST_PIPELINE (m_gst_playbin)), gstBusSyncHandler, this);
		char srt_filename[strlen(filename)+1];
		strncpy(srt_filename,filename,strlen(filename)-3);
		srt_filename[strlen(filename)-3]='\0';
		strcat(srt_filename, "srt");
		struct stat buffer;
		if (stat(srt_filename, &buffer) == 0)
		{
			eDebug("eServiceMP3::subtitle uri: %s", g_filename_to_uri(srt_filename, NULL, NULL));
			g_object_set (G_OBJECT (m_gst_playbin), "suburi", g_filename_to_uri(srt_filename, NULL, NULL), NULL);
		}
		if ( m_sourceinfo.is_streaming )
		{
			g_signal_connect (G_OBJECT (m_gst_playbin), "notify::source", G_CALLBACK (gstHTTPSourceSetAgent), this);
		}
	} else
	{
		m_event((iPlayableService*)this, evUser+12);

		if (m_gst_playbin)
			gst_object_unref(GST_OBJECT(m_gst_playbin));

		eDebug("eServiceMP3::sorry, can't play: %s",m_errorInfo.error_message.c_str());
		m_gst_playbin = 0;
	}

	setBufferSize(m_buffer_size);
}