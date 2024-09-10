ADGameDescList AdvancedMetaEngine::detectGame(const Common::FSNode &parent, const FileMap &allFiles, Common::Language language, Common::Platform platform, const Common::String &extra) const {
	ADFilePropertiesMap filesProps;

	const ADGameFileDescription *fileDesc;
	const ADGameDescription *g;
	const byte *descPtr;

	debug(3, "Starting detection in dir '%s'", parent.getPath().c_str());

	// Check which files are included in some ADGameDescription *and* are present.
	// Compute MD5s and file sizes for these files.
	for (descPtr = _gameDescriptors; ((const ADGameDescription *)descPtr)->gameId != 0; descPtr += _descItemSize) {
		g = (const ADGameDescription *)descPtr;

		for (fileDesc = g->filesDescriptions; fileDesc->fileName; fileDesc++) {
			Common::String fname = fileDesc->fileName;
			ADFileProperties tmp;

			if (filesProps.contains(fname))
				continue;

			if (getFileProperties(parent, allFiles, *g, fname, tmp)) {
				debug(3, "> '%s': '%s'", fname.c_str(), tmp.md5.c_str());
				filesProps[fname] = tmp;
			}
		}
	}

	ADGameDescList matched;
	ADGameIdList matchedGameIds;
	int maxFilesMatched = 0;
	bool gotAnyMatchesWithAllFiles = false;

	// MD5 based matching
	uint i;
	for (i = 0, descPtr = _gameDescriptors; ((const ADGameDescription *)descPtr)->gameId != 0; descPtr += _descItemSize, ++i) {
		g = (const ADGameDescription *)descPtr;
		bool fileMissing = false;

		// Do not even bother to look at entries which do not have matching
		// language and platform (if specified).
		if ((language != Common::UNK_LANG && g->language != Common::UNK_LANG && g->language != language
			 && !(language == Common::EN_ANY && (g->flags & ADGF_ADDENGLISH))) ||
			(platform != Common::kPlatformUnknown && g->platform != Common::kPlatformUnknown && g->platform != platform)) {
			continue;
		}

		if ((_flags & kADFlagUseExtraAsHint) && !extra.empty() && g->extra != extra)
			continue;

		bool allFilesPresent = true;
		int curFilesMatched = 0;
		bool hashOrSizeMismatch = false;

		// Try to match all files for this game
		for (fileDesc = g->filesDescriptions; fileDesc->fileName; fileDesc++) {
			Common::String tstr = fileDesc->fileName;

			if (!filesProps.contains(tstr)) {
				fileMissing = true;
				allFilesPresent = false;
				break;
			}

			if (hashOrSizeMismatch)
				continue;

			if (fileDesc->md5 != NULL && fileDesc->md5 != filesProps[tstr].md5) {
				debug(3, "MD5 Mismatch. Skipping (%s) (%s)", fileDesc->md5, filesProps[tstr].md5.c_str());
				fileMissing = true;
				hashOrSizeMismatch = true;
				continue;
			}

			if (fileDesc->fileSize != -1 && fileDesc->fileSize != filesProps[tstr].size) {
				debug(3, "Size Mismatch. Skipping");
				fileMissing = true;
				hashOrSizeMismatch = true;
				continue;
			}

			debug(3, "Matched file: %s", tstr.c_str());
			curFilesMatched++;
		}

		// We found at least one entry with all required files present.
		// That means that we got new variant of the game.
		//
		// Without this check we would have erroneous checksum display
		// where only located files will be enlisted.
		//
		// Potentially this could rule out variants where some particular file
		// is really missing, but the developers should better know about such
		// cases.
		if (allFilesPresent) {
			gotAnyMatchesWithAllFiles = true;
			if (!matchedGameIds.size() || strcmp(matchedGameIds.back(), g->gameId) != 0)
				matchedGameIds.push_back(g->gameId);
		}

		if (!fileMissing) {
			debug(2, "Found game: %s (%s %s/%s) (%d)", g->gameId, g->extra,
			 getPlatformDescription(g->platform), getLanguageDescription(g->language), i);

			if (curFilesMatched > maxFilesMatched) {
				debug(2, " ... new best match, removing all previous candidates");
				maxFilesMatched = curFilesMatched;

				matched.clear();	// Remove any prior, lower ranked matches.
				matched.push_back(g);
			} else if (curFilesMatched == maxFilesMatched) {
				matched.push_back(g);
			} else {
				debug(2, " ... skipped");
			}

		} else {
			debug(5, "Skipping game: %s (%s %s/%s) (%d)", g->gameId, g->extra,
			 getPlatformDescription(g->platform), getLanguageDescription(g->language), i);
		}
	}

	// We didn't find a match
	if (matched.empty()) {
		if (!filesProps.empty() && gotAnyMatchesWithAllFiles) {
			reportUnknown(parent, filesProps, matchedGameIds);
		}

		// Filename based fallback
	}

	return matched;
}