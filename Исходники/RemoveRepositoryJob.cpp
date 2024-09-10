status_t
RemoveRepositoryJob::Execute()
{
	BPackageRoster roster;
	BRepositoryConfig repoConfig;
	status_t result = roster.GetRepositoryConfig(fRepositoryName, &repoConfig);
	if (result != B_OK) {
		if (result == B_ENTRY_NOT_FOUND) {
			BString error = BString("repository '") << fRepositoryName
				<< "' not found!";
			SetErrorString(error);
		}
		return result;
	}

	BString question = BString("Really remove the repository '")
		<< fRepositoryName << "'?";
	bool yes = fContext.DecisionProvider().YesNoDecisionNeeded("", question,
		"yes", "no", "no");
	if (!yes)
		return B_CANCELED;

	BEntry repoConfigEntry = repoConfig.Entry();
	if ((result = repoConfigEntry.Remove()) != B_OK)
		return result;

	BRepositoryCache repoCache;
	if (roster.GetRepositoryCache(fRepositoryName, &repoCache) == B_OK) {
		BEntry repoCacheEntry = repoCache.Entry();
		if ((result = repoCacheEntry.Remove()) != B_OK)
			return result;
	}

	return B_OK;
}