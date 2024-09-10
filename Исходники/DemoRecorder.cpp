CDemoRecorder::CDemoRecorder()
{
	// We want this folder to exist
	if (!filesystem.CreateDirectory("demos"))
		return;

	wantedName = demoName = "demos/unnamed.sdf";

	std::string filename = filesystem.LocateFile(demoName, FileSystem::WRITE);
	recordDemo = SAFE_NEW std::ofstream(filename.c_str(), std::ios::out | std::ios::binary);

	memset(&fileHeader, 0, sizeof(DemoFileHeader));
	strcpy(fileHeader.magic, DEMOFILE_MAGIC);
	fileHeader.version = DEMOFILE_VERSION;
	fileHeader.headerSize = sizeof(DemoFileHeader);
	strcpy(fileHeader.versionString, VERSION_STRING);

	__time64_t currtime;
	_time64(&currtime);
	fileHeader.unixTime = currtime;

	recordDemo->write((char*)&fileHeader, sizeof(fileHeader));

	if (gameSetup) {
		// strip trailing null termination characters
		int length = gameSetup->gameSetupTextLength;
		while (gameSetup->gameSetupText[length - 1] == '\0')
			--length;

		fileHeader.scriptSize = length;
		recordDemo->write(gameSetup->gameSetupText, length);
	}

	fileHeader.playerStatElemSize = sizeof(CPlayer::Statistics);
	fileHeader.teamStatElemSize = sizeof(CTeam::Statistics);
	fileHeader.teamStatPeriod = CTeam::statsPeriod;
	fileHeader.winningAllyTeam = -1;

	WriteFileHeader();
}