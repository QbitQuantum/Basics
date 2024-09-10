SpotifySession::SpotifySession() :
		loggedInEvent(CreateEvent(NULL, FALSE, FALSE, NULL)),
		threadData(spotifyCS), decoderOwner(NULL) {

	processEventsEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	threadData.processEventsEvent = processEventsEvent;
	threadData.sess = getAnyway();

	memset(&initOnce, 0, sizeof(INIT_ONCE));

	static sp_session_callbacks session_callbacks = {};
	static sp_session_config spconfig = {};

	PWSTR path;
	if (SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path))
		throw pfc::exception("couldn't get local app data path");

	size_t num;
	char lpath[MAX_PATH];
	if (wcstombs_s(&num, lpath, MAX_PATH, path, MAX_PATH)) {
		CoTaskMemFree(path);
		throw pfc::exception("couldn't convert local app data path");
	}
	CoTaskMemFree(path);

	if (strcat_s(lpath, "\\foo_input_spotify"))
		throw pfc::exception("couldn't append to path");

	spconfig.api_version = SPOTIFY_API_VERSION,
	spconfig.cache_location = lpath;
	spconfig.settings_location = lpath;
	spconfig.application_key = g_appkey;
	spconfig.application_key_size = g_appkey_size;
	spconfig.user_agent = "spotify-foobar2000-faux-" MYVERSION;
	spconfig.userdata = this;
	spconfig.callbacks = &session_callbacks;

	session_callbacks.logged_in = &logged_in;
	session_callbacks.notify_main_thread = &notify_main_thread;
	session_callbacks.music_delivery = &music_delivery;
	session_callbacks.play_token_lost = &play_token_lost;
	session_callbacks.end_of_track = &end_of_track;
	session_callbacks.log_message = &log_message;
	session_callbacks.message_to_user = &message_to_user;
	session_callbacks.start_playback = &start_playback;

	{
		LockedCS lock(spotifyCS);

		if (NULL == CreateThread(NULL, 0, &spotifyThread, &threadData, 0, NULL)) {
			throw pfc::exception("Couldn't create thread");
		}

		assertSucceeds("creating session", sp_session_create(&spconfig, &sp));
	}
}