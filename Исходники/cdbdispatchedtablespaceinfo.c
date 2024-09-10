/*
 * add a entry into DispatchedFilespaceDirHashTable,
 * replace it if already exist
 */
void
DispatchedFilespace_AddForTablespace(Oid tablespace, const char * path)
{
	bool found;
	DispatchedFilespaceDirEntry entry;

	Assert(NULL != path);

	if (!DispatchedFilespaceDirHashTable)
	{
		DispatchedFilespace_HashTableInit();
	}

	entry = (DispatchedFilespaceDirEntry) hash_search(
			DispatchedFilespaceDirHashTable, (void *) &tablespace, HASH_ENTER,
			&found);

	Assert(NULL != entry);

	StrNCpy(entry->location, path, FilespaceLocationBlankPaddedWithNullTermLen);
}