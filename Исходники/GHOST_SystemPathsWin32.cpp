void GHOST_SystemPathsWin32::addToSystemRecentFiles(const char *filename) const
{
	/* SHARD_PATH resolves to SHARD_PATHA for non-UNICODE build */
	UTF16_ENCODE(filename);
	SHAddToRecentDocs(SHARD_PATHW, filename_16);
	UTF16_UN_ENCODE(filename);
}