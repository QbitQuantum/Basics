void PlaybackFile::checkRecordedMD5() {
	uint8 currentMD5[16];
	uint8 savedMD5[16];
	Graphics::Surface screen;
	_readStream->read(savedMD5, 16);
	if (!g_eventRec.grabScreenAndComputeMD5(screen, currentMD5)) {
		return;
	}
	uint32 seconds = g_system->getMillis(true) / 1000;
	String screenTime = String::format("%.2d:%.2d:%.2d", seconds / 3600 % 24, seconds / 60 % 60, seconds % 60);
	if (memcmp(savedMD5, currentMD5, 16) != 0) {
		debugC(1, kDebugLevelEventRec, "playback:action=\"Check screenshot\" time=%s result = fail", screenTime.c_str());
		warning("Recorded and current screenshots are different");
	} else {
		debugC(1, kDebugLevelEventRec, "playback:action=\"Check screenshot\" time=%s result = success", screenTime.c_str());
	}
	Graphics::saveThumbnail(*_screenshotsFile, screen);
	screen.free();
}