	void Initialize() {
		_downloader = std::make_shared<BackgroundDownloader>();
		_player = std::make_shared<MusicPlayer>();
		_downloader->initialize();
		_player->initialize();
	}