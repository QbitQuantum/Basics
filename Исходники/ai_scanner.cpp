AIInfo *AIScannerInfo::FindInfo(const char *nameParam, int versionParam, bool force_exact_match)
{
	if (this->info_list.size() == 0) return NULL;
	if (nameParam == NULL) return NULL;

	char ai_name[1024];
	strecpy(ai_name, nameParam, lastof(ai_name));
	strtolower(ai_name);

	AIInfo *info = NULL;
	int version = -1;

	if (versionParam == -1) {
		/* We want to load the latest version of this AI; so find it */
		if (this->info_single_list.find(ai_name) != this->info_single_list.end()) return static_cast<AIInfo *>(this->info_single_list[ai_name]);

		/* If we didn't find a match AI, maybe the user included a version */
		char *e = strrchr(ai_name, '.');
		if (e == NULL) return NULL;
		*e = '\0';
		e++;
		versionParam = atoi(e);
		/* FALL THROUGH, like we were calling this function with a version. */
	}

	if (force_exact_match) {
		/* Try to find a direct 'name.version' match */
		char ai_name_tmp[1024];
		seprintf(ai_name_tmp, lastof(ai_name_tmp), "%s.%d", ai_name, versionParam);
		strtolower(ai_name_tmp);
		if (this->info_list.find(ai_name_tmp) != this->info_list.end()) return static_cast<AIInfo *>(this->info_list[ai_name_tmp]);
	}

	/* See if there is a compatible AI which goes by that name, with the highest
	 *  version which allows loading the requested version */
	ScriptInfoList::iterator it = this->info_list.begin();
	for (; it != this->info_list.end(); it++) {
		AIInfo *i = static_cast<AIInfo *>((*it).second);
		if (strcasecmp(ai_name, i->GetName()) == 0 && i->CanLoadFromVersion(versionParam) && (version == -1 || i->GetVersion() > version)) {
			version = (*it).second->GetVersion();
			info = i;
		}
	}

	return info;
}