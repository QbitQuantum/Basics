static int filter_apply(
	git_filter				*self,
	void					**payload, /* may be read and/or set */
	git_buf					*to,
	const git_buf			*from,
	const git_filter_source	*src)
{
	struct filter_filter *ffs = (struct filter_filter *)self;
	git_config *config;
	git_buf configKey = GIT_BUF_INIT;
	int isRequired = FALSE;
	int error;
	const char *cmd = NULL;
	git_buf cmdBuf = GIT_BUF_INIT;
	wchar_t *wide_cmd;
	COMMAND_HANDLE commandHandle = COMMAND_HANDLE_INIT;
	git_buf errBuf = GIT_BUF_INIT;
	DWORD exitCode;

	if (!*payload)
		return GIT_PASSTHROUGH;

	if (git_repository_config__weakptr(&config, git_filter_source_repo(src)))
		return -1;

	git_buf_join3(&configKey, '.', "filter", *payload, "required");
	if (git_buf_oom(&configKey))
		return -1;

	error = git_config_get_bool(&isRequired, config, configKey.ptr);
	git_buf_free(&configKey);
	if (error && error != GIT_ENOTFOUND)
		return -1;

	git_buf_join(&configKey, '.', "filter", *payload);
	if (git_filter_source_mode(src) == GIT_FILTER_SMUDGE) {
		git_buf_puts(&configKey, ".smudge");
	} else {
		git_buf_puts(&configKey, ".clean");
	}
	if (git_buf_oom(&configKey))
		return -1;

	error = git_config_get_string(&cmd, config, configKey.ptr);
	git_buf_free(&configKey);
	if (error && error != GIT_ENOTFOUND)
		return -1;

	if (error == GIT_ENOTFOUND) {
		if (isRequired)
			return -1;
		return GIT_PASSTHROUGH;
	}

	git_buf_puts(&cmdBuf, cmd);
	if (git_buf_oom(&cmdBuf))
		return -1;

	if (expandPerCentF(&cmdBuf, git_filter_source_path(src)))
		return 1;

	if (ffs->shexepath) {
		// build params for sh.exe
		git_buf shParams = GIT_BUF_INIT;
		git_buf_puts(&shParams, " -c \"");
		git_buf_text_puts_escaped(&shParams, cmdBuf.ptr, "\"\\", "\\");
		git_buf_puts(&shParams, "\"");
		git_buf_swap(&shParams, &cmdBuf);
		git_buf_free(&shParams);
	}

	if (git__utf8_to_16_alloc(&wide_cmd, cmdBuf.ptr) < 0)
	{
		git_buf_free(&cmdBuf);
		return 1;
	}
	git_buf_free(&cmdBuf);

	if (ffs->shexepath) {
		// build cmd, i.e. shexepath + params
		size_t len = wcslen(ffs->shexepath) + wcslen(wide_cmd) + 1;
		wchar_t *tmp = git__calloc(len, sizeof(wchar_t));
		if (!tmp) {
			git__free(wide_cmd);
			return -1;
		}
		wcscat_s(tmp, len, ffs->shexepath);
		wcscat_s(tmp, len, wide_cmd);
		git__free(wide_cmd);
		wide_cmd = tmp;
	}

	commandHandle.errBuf = &errBuf;
	if (command_start(wide_cmd, &commandHandle, ffs->pEnv)) {
		git__free(wide_cmd);
		if (isRequired)
			return -1;
		return GIT_PASSTHROUGH;
	}
	git__free(wide_cmd);

	if (commmand_start_stdout_reading_thread(&commandHandle, to)) {
		command_close(&commandHandle);
		return -1;
	}

	if (command_write_gitbuf(&commandHandle, from)) {
		DWORD exitCode = command_close(&commandHandle);
		if (exitCode)
			setProcessError(exitCode, &errBuf);
		git_buf_free(&errBuf);
		if (isRequired)
			return -1;
		return GIT_PASSTHROUGH;
	}
	command_close_stdin(&commandHandle);

	if (command_wait_stdout_reading_thread(&commandHandle)) {
		DWORD exitCode = command_close(&commandHandle);
		if (exitCode)
			setProcessError(exitCode, &errBuf);
		git_buf_free(&errBuf);
		if (isRequired)
			return -1;
		return GIT_PASSTHROUGH;
	}

	exitCode = command_close(&commandHandle);
	if (exitCode) {
		if (isRequired) {
			setProcessError(exitCode, &errBuf);
			git_buf_free(&errBuf);
			return -1;
		}
		git_buf_free(&errBuf);
		return GIT_PASSTHROUGH;
	}

	git_buf_free(&errBuf);

	return 0;
}