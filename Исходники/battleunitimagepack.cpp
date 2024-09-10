const UString BattleUnitImagePack::getNameFromID(UString id)
{
	static const UString emptyString = "";
	if (id.length() == 0)
		return emptyString;
	auto plen = getPrefix().length();
	if (id.length() > plen)
		return id.substr(plen, id.length() - plen);
	LogError("Invalid BattleUnitImagePack ID %s", id);
	return emptyString;
}