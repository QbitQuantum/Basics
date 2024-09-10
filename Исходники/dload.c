/** Fetch a remote pkg. */
char SYMEXPORT *alpm_fetch_pkgurl(alpm_handle_t *handle, const char *url)
{
	char *filepath;
	const char *cachedir;
	char *final_file = NULL;
	struct dload_payload payload;
	int ret;

	CHECK_HANDLE(handle, return NULL);
	ASSERT(url, RET_ERR(handle, ALPM_ERR_WRONG_ARGS, NULL));

	/* find a valid cache dir to download to */
	cachedir = _alpm_filecache_setup(handle);

	memset(&payload, 0, sizeof(struct dload_payload));
	payload.handle = handle;
	STRDUP(payload.fileurl, url, RET_ERR(handle, ALPM_ERR_MEMORY, NULL));
	payload.allow_resume = 1;

	/* download the file */
	ret = _alpm_download(&payload, cachedir, &final_file);
	_alpm_dload_payload_reset(&payload);
	if(ret == -1) {
		_alpm_log(handle, ALPM_LOG_WARNING, _("failed to download %s\n"), url);
		free(final_file);
		return NULL;
	}
	_alpm_log(handle, ALPM_LOG_DEBUG, "successfully downloaded %s\n", url);

	/* attempt to download the signature */
	if(ret == 0 && (handle->siglevel & ALPM_SIG_PACKAGE)) {
		char *sig_final_file = NULL;
		size_t len;

		len = strlen(url) + 5;
		MALLOC(payload.fileurl, len, RET_ERR(handle, ALPM_ERR_MEMORY, NULL));
		snprintf(payload.fileurl, len, "%s.sig", url);
		payload.handle = handle;
		payload.force = 1;
		payload.errors_ok = (handle->siglevel & ALPM_SIG_PACKAGE_OPTIONAL);

		ret = _alpm_download(&payload, cachedir, &sig_final_file);
		if(ret == -1 && !payload.errors_ok) {
			_alpm_log(handle, ALPM_LOG_WARNING,
					_("failed to download %s\n"), payload.fileurl);
			/* Warn now, but don't return NULL. We will fail later during package
			 * load time. */
		} else if(ret == 0) {
			_alpm_log(handle, ALPM_LOG_DEBUG,
					"successfully downloaded %s\n", payload.fileurl);
		}
		FREE(sig_final_file);
		_alpm_dload_payload_reset(&payload);
	}

	/* we should be able to find the file the second time around */
	filepath = _alpm_filecache_find(handle, final_file);
	free(final_file);

	return filepath;
}