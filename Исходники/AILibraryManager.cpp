std::vector<SkirmishAIKey> CAILibraryManager::FittingSkirmishAIKeys(
		const SkirmishAIKey& skirmishAIKey) const {

	std::vector<SkirmishAIKey> applyingKeys;

	if (skirmishAIKey.IsUnspecified()) {
		return applyingKeys;
	}

	bool checkVersion = false;
	if (skirmishAIKey.GetVersion() != "") {
		checkVersion = true;
	}

	std::set<SkirmishAIKey>::const_iterator sasi;
	for (sasi=skirmishAIKeys.begin(); sasi!=skirmishAIKeys.end(); sasi++) {

		// check if the ai name fits
		if (skirmishAIKey.GetShortName() != sasi->GetShortName()) {
			continue;
		}

		// check if the ai version fits (if one is specified)
		if (checkVersion && skirmishAIKey.GetVersion() != sasi->GetVersion()) {
			continue;
		}

		// if the programm raches here, we know that this key fits
		applyingKeys.push_back(*sasi);
	}

	return applyingKeys;
}