void Plugin_Init()
{
	static_assert(IOCPThreadCount > 0, "Specify a positive number of threads");

	for(int i=0 ; i<IOCPThreadCount ; i++)
		::CloseHandle(::CreateThread(nullptr, 0, &IOServiceRunThread, nullptr, 0, nullptr));

	io_sync_mutex = ::CreateEvent(nullptr, FALSE, FALSE, NULL);
	forwarder.reset(new OutForwarder(_T("out_ds.dll")));
	mpdClient.reset(new MpdClient(Global::Settings.router_host.c_str(), Global::Settings.router_port, io_service));
	
#ifdef STREAMER_PAYD_VERSION
	//Global::Settings.output_buffer_lenght = 10000;
	SyncronisedStreamManager::Options playbackOptions = { Global::Settings.output_buffer_lenght, *forwarder.get(), Global::Settings.forward_output_sound };

	//streamManager.reset(new DummyStreamManager(std::unique_ptr<IAudioOutputStream>(new Mp3OutputStream()), *mpdClient, playbackOptions.prebuffer_time));
	streamManager.reset(new SyncronisedStreamManager(std::unique_ptr<IAudioOutputStream>(new Mp3OutputStream()), *mpdClient, *_winamp_player, io_service, playbackOptions));
	//streamManager.reset(new SyncronisedStreamManager(std::unique_ptr<IAudioOutputStream>(new WavOutputStream()), *mpdClient, *_winamp_player, io_service, playbackOptions));
#else
	Global::Settings.output_buffer_lenght = 2000;

	streamManager.reset(new DummyStreamManager(std::unique_ptr<IAudioOutputStream>(new Mp3OutputStream()), *mpdClient, Global::Settings.output_buffer_lenght));
#endif

	streamer.reset(new HttpServer(*streamManager, io_service));

	forwarder->Init();

	if (! streamer->Start() )
		Global::DebugWrite(_T("Server not started !!!"));
	Global::ListeningPort = streamer->GetListeningPort();

	streamManager->initialize();

#ifndef STREAMER_PAYD_VERSION
	forwarder->EnableOutput(false);
#endif

	Plugin::check_for_update_async(io_service);
}