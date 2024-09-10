Common::Error BladeRunnerEngine::saveGameState(int slot, const Common::String &desc) {
	Common::OutSaveFile *saveFile = BladeRunner::SaveFileManager::openForSaving(_targetName, slot);
	if (saveFile == nullptr || saveFile->err()) {
		delete saveFile;
		return Common::kReadingFailed;
	}

	Graphics::Surface thumbnail = generateThumbnail();

	BladeRunner::SaveFileHeader header;
	header._name = desc;

	BladeRunner::SaveFileManager::writeHeader(*saveFile, header);

	saveGame(*saveFile, thumbnail);

	saveFile->finalize();

	thumbnail.free();

	delete saveFile;

	return Common::kNoError;
}