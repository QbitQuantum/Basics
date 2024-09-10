void
LiveQuery::_PerformQuery(BQuery& query)
{
	status_t status = query.Fetch();
	if (status != B_OK) {
		fprintf(stderr, "%s: bad query expression\n", kProgramName);
		return;
	}

	int32 count = 0;

	BEntry entry;
	BPath path;
	while (query.GetNextEntry(&entry) == B_OK) {
		if (sFilesOnly && !entry.IsFile())
			continue;

		if (entry.GetPath(&path) != B_OK) {
			fprintf(stderr, "%s: could not get path for entry\n", kProgramName);
			continue;
		}

		printf("%s\n", sEscapeMetaChars ? BString().CharacterEscape(
				path.Path(), " ()?*&\"'[]^\\~|;!<>*$\t", '\\').String()
			: path.Path());

		count++;
	}

	printf("FOUND %ld entries\n", count);
}