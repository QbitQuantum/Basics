BOOL Pointer::ADDRawKeys(const char* owner, const char* classic, const char* lod)
{
	strncat_s(Vars.szKeyOwner, owner, strlen(owner)); //for add in later
	strncat_s(Vars.szClassic, classic, strlen(classic));
	strncat_s(Vars.szLod, lod, strlen(lod));

	if (classic && lod != NULL) {
		Pointer::InstallRawInfo();
		return true;
	}
	return false;
}