static int tcommit_one(struct tfile_t* tf, size_t off)
{
	#ifdef __WINNT__
	wchar_t* wtf = 0;
	wchar_t* wf = 0;
	#endif
	int old_errno;

	if (fchmod(tf->fd, tf->mode))
		goto err;
#if 0
	/* TODO: make this optional */
	if (fsync(tf->fd))
		goto err;
#endif
	if (close(tf->fd))
		goto err;
	/* TODO: rename is broken on windows. it doesn't allow to replace
	 * exising files atomically. see google for existing implementations
	 * and replace rename() for windows targets with a suitable one. */
#ifdef __WINNT__
	wtf = utf8_to_ucs2(tf->tmpfilename);
	wf = utf8_to_ucs2(tf->filename);
	if (!wtf || !wf)
		goto err;
	if (_wrename(wtf, wf))
		goto err;
	free(wtf);
	free(wf);
#else
	if (rename(tf->tmpfilename, tf->filename))
		goto err;
#endif
	free(tf->filename);
	free(tf->tmpfilename);
	pool_cut(&mappool, off, sizeof(struct tfile_t));
	return 0;
err:
	#ifdef __WINNT__
	if (wtf)
		free(wtf);
	if (wf)
		free(wf);
	#endif
	old_errno = errno;
	trollback_one(tf, off);
	errno = old_errno;
	return -1;
}