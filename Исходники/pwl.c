static void
enchant_unlock_file (FILE * f)
{
#if defined(HAVE_FLOCK)
	flock (fileno (f), LOCK_UN);
#elif defined(HAVE_LOCKF)
	lockf (fileno (f), F_ULOCK, 0);
#elif defined(_WIN32)
	OVERLAPPED overlapped;

	overlapped.Offset = 0;
	overlapped.OffsetHigh = 0;
	overlapped.hEvent = NULL;
	if (!UnlockFileEx ((HANDLE) _get_osfhandle (fileno (f)), 0, 0, 0x80000000, &overlapped))
		g_warning ("Could not unlock file\n");
#else
	/* TODO: UNIX fcntl. This race condition probably isn't too bad. */
#endif /* HAVE_FLOCK */
}