CSkirmishAILibrary::CSkirmishAILibrary(const SSkirmishAILibrary& ai,
		const SkirmishAIKey& key)
		: sSAI(ai), key(key) {

	if (sSAI.handleEvent == NULL) {
		LOG_L(L_ERROR,
				"Fetched AI library %s-%s has no handleEvent function"
				"available. It is therefore illegal and will not be used."
				"This usually indicates a problem in the used AI Interface"
				"library (%s-%s).",
				key.GetShortName().c_str(), key.GetVersion().c_str(),
				key.GetInterface().GetShortName().c_str(),
				key.GetInterface().GetVersion().c_str());
	}
}