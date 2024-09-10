U32 ProcessorInfo::GetCacheSize(int level, CACHE_TYPE cacheType)
{
	U32 szCache = 0;
	DWORD buffer_size = 0;
	DWORD i = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

	GetLogicalProcessorInformation(0, &buffer_size);
	buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
	GetLogicalProcessorInformation(&buffer[0], &buffer_size);

	for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i)
	{
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == level) {
			szCache = buffer[i].Cache.Size;
			break;
		}
	}

	free(buffer);
	return szCache;
}