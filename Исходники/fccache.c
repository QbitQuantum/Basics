/*
 * Map a cache file into memory
 */
static FcCache *
FcDirCacheMapFd (int fd, struct stat *fd_stat, struct stat *dir_stat)
{
    FcCache	*cache;
    FcBool	allocated = FcFalse;

    if (fd_stat->st_size < (int) sizeof (FcCache))
	return NULL;
    cache = FcCacheFindByStat (fd_stat);
    if (cache)
    {
	if (FcCacheTimeValid (cache, dir_stat))
	    return cache;
	FcDirCacheUnload (cache);
	cache = NULL;
    }

    /*
     * Large cache files are mmap'ed, smaller cache files are read. This
     * balances the system cost of mmap against per-process memory usage.
     */
    if (FcCacheIsMmapSafe (fd) && fd_stat->st_size >= FC_CACHE_MIN_MMAP)
    {
#if defined(HAVE_MMAP) || defined(__CYGWIN__)
	cache = mmap (0, fd_stat->st_size, PROT_READ, MAP_SHARED, fd, 0);
#ifdef HAVE_POSIX_FADVISE
	posix_fadvise (fd, 0, fd_stat->st_size, POSIX_FADV_WILLNEED);
#endif
	if (cache == MAP_FAILED)
	    cache = NULL;
#elif defined(_WIN32)
	{
	    HANDLE hFileMap;

	    cache = NULL;
	    hFileMap = CreateFileMapping((HANDLE) _get_osfhandle(fd), NULL,
					 PAGE_READONLY, 0, 0, NULL);
	    if (hFileMap != NULL)
	    {
		cache = MapViewOfFile (hFileMap, FILE_MAP_READ, 0, 0,
				       fd_stat->st_size);
		CloseHandle (hFileMap);
	    }
	}
#endif
    }
    if (!cache)
    {
	cache = malloc (fd_stat->st_size);
	if (!cache)
	    return NULL;

	if (read (fd, cache, fd_stat->st_size) != fd_stat->st_size)
	{
	    free (cache);
	    return NULL;
	}
	allocated = FcTrue;
    }
    if (cache->magic != FC_CACHE_MAGIC_MMAP ||
	cache->version < FC_CACHE_CONTENT_VERSION ||
	cache->size != (intptr_t) fd_stat->st_size ||
	!FcCacheTimeValid (cache, dir_stat) ||
	!FcCacheInsert (cache, fd_stat))
    {
	if (allocated)
	    free (cache);
	else
	{
#if defined(HAVE_MMAP) || defined(__CYGWIN__)
	    munmap (cache, fd_stat->st_size);
#elif defined(_WIN32)
	    UnmapViewOfFile (cache);
#endif
	}
	return NULL;
    }

    /* Mark allocated caches so they're freed rather than unmapped */
    if (allocated)
	cache->magic = FC_CACHE_MAGIC_ALLOC;
	
    return cache;
}