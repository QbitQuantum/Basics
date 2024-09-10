uint32 TalkTable_TLK::getLanguageID(const Common::UString &file) {
	Common::ReadFile tlk;
	if (!tlk.open(file))
		return kLanguageInvalid;

	return getLanguageID(tlk);
}