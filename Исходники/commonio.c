int
commonio_close(struct commonio_db *db)
{
	char buf[1024];
	int errors = 0;
	struct stat sb;

	if (!db->isopen) {
		errno = EINVAL;
		return 0;
	}
	db->isopen = 0;

	if (!db->changed || db->readonly) {
		fclose(db->fp);
		db->fp = NULL;
		goto success;
	}

	memzero(&sb, sizeof sb);
	if (db->fp) {
		if (fstat(fileno(db->fp), &sb)) {
			fclose(db->fp);
			db->fp = NULL;
			goto fail;
		}

		/*
		 * Create backup file.
		 */
		snprintf(buf, sizeof buf, "%s-", db->filename);

		if (create_backup(buf, db->fp))
			errors++;

		if (fclose(db->fp))
			errors++;

		if (errors) {
			db->fp = NULL;
			goto fail;
		}
	} else {
		/*
		 * Default permissions for new [g]shadow files.
		 * (passwd and group always exist...)
		 */
		sb.st_mode = 0400;
		sb.st_uid = 0;
		sb.st_gid = 0;
	}

	snprintf(buf, sizeof buf, "%s+", db->filename);

	db->fp = fopen_set_perms(buf, "w", &sb);
	if (!db->fp)
		goto fail;

	if (write_all(db))
		errors++;

	if (fflush(db->fp))
		errors++;
#ifdef HAVE_FSYNC
	if (fsync(fileno(db->fp)))
		errors++;
#else
	sync();
#endif
	if (fclose(db->fp))
		errors++;

	db->fp = NULL;

	if (errors) {
		unlink(buf);
		goto fail;
	}

	if (rename(buf, db->filename))
		goto fail;

	nscd_need_reload = 1;

success:
	free_linked_list(db);
	return 1;

fail:
	free_linked_list(db);
	return 0;
}