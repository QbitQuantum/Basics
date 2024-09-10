void
add_filesystem_credential_to_cache(const char * uri, char *token)
{
	char *protocol;
	char *host;

	bool found = false;
	struct FileSystemCredential *entry;
	struct FileSystemCredentialKey key;
    HTAB * currentFilesystemCredentials;
    MemoryContext currentFilesystemCredentialsMemoryContext;

	Assert(NULL != token);

	get_current_credential_cache_and_memcxt(&currentFilesystemCredentials,
	        &currentFilesystemCredentialsMemoryContext);

	Insist(NULL != currentFilesystemCredentials);
	Insist(NULL != currentFilesystemCredentialsMemoryContext);

	MemoryContext old = MemoryContextSwitchTo(
			currentFilesystemCredentialsMemoryContext);

	memset(&key, 0, sizeof(key));

	if (HdfsParsePath(uri, &protocol, &host, &key.port, NULL)
			|| NULL == protocol || NULL == host)
		elog(ERROR, "fail to parse uri: %s", uri);

	StrNCpy(key.protocol, protocol, sizeof(key.protocol));
	StrNCpy(key.host, host, sizeof(key.host));

	entry = (struct FileSystemCredential *) hash_search(
			currentFilesystemCredentials, &key, HASH_ENTER, &found);

	if (!found) {
		entry->credential = pstrdup(token);
	}

	MemoryContextSwitchTo(old);
}