bool WintermuteEngine::getGameInfo(const Common::FSList &fslist, Common::String &name, Common::String &caption) {
	bool retVal = false;
	caption = name = "(invalid)";
	Common::SeekableReadStream *stream = NULL;
	// Quick-fix, instead of possibly breaking the persistence-system, let's just roll with it
	BaseFileManager *fileMan = new BaseFileManager(Common::UNK_LANG);
	fileMan->registerPackages(fslist);
	stream = fileMan->openFile("startup.settings", false, false);

	// The process is as follows: Check the "GAME=" tag in startup.settings, to decide where the
	// game-settings are (usually "default.game"), then look into the game-settings to find
	// the NAME = and CAPTION = tags, to use them to generate a gameid and extras-field

	Common::String settingsGameFile = "default.game";
	// If the stream-open failed, lets at least attempt to open the default game file afterwards
	// so, we don't call it a failure yet.
	if (stream) {
		while (!stream->eos() && !stream->err()) {
			Common::String line = stream->readLine();
			line.trim(); // Get rid of indentation
			// Expect "SETTINGS {" or comment, or empty line
			if (line.size() == 0 || line[0] == ';' || (line.contains("{"))) {
				continue;
			} else {
				// We are looking for "GAME ="
				Common::StringTokenizer token(line, "=");
				Common::String key = token.nextToken();
				Common::String value = token.nextToken();
				if (value.size() == 0) {
					continue;
				}
				if (value[0] == '\"') {
					value.deleteChar(0);
				} else {
					continue;
				}
				if (value.lastChar() == '\"') {
					value.deleteLastChar();
				}
				if (key == "GAME") {
					settingsGameFile = value;
					break;
				}
			}
		}
	}

	delete stream;
	stream = fileMan->openFile(settingsGameFile, false, false);
	if (stream) {
		// We do some manual parsing here, as the engine needs gfx to be initalized to do that.
		while (!stream->eos() && !stream->err()) {
			Common::String line = stream->readLine();
			line.trim(); // Get rid of indentation
			// Expect "GAME {" or comment, or empty line
			if (line.size() == 0 || line[0] == ';' || (line.contains("{"))) {
				continue;
			} else {
				Common::StringTokenizer token(line, "=");
				Common::String key = token.nextToken();
				Common::String value = token.nextToken();
				if (value.size() == 0) {
					continue;
				}
				if (value[0] == '\"') {
					value.deleteChar(0);
				} else {
					continue;    // not a string
				}
				if (value.lastChar() == '\"') {
					value.deleteLastChar();
				}
				if (key == "NAME") {
					retVal = true;
					name = value;
				} else if (key == "CAPTION") {
					retVal = true;
					caption = value;
				}
			}
		}
		delete stream;
	}
	delete fileMan;
	BaseEngine::destroy();
	return retVal;
}