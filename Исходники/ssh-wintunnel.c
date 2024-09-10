static int _git_ssh_setup_tunnel(
	ssh_subtransport *t,
	const char *url,
	const char *gitCmd,
	git_smart_subtransport_stream **stream)
{
	char *host = NULL, *port = NULL, *path = NULL, *user = NULL, *pass = NULL;
	size_t i;
	ssh_stream *s;
	wchar_t *ssh = t->sshtoolpath;
	wchar_t *wideParams = NULL;
	wchar_t *cmd = NULL;
	git_buf params = GIT_BUF_INIT;
	int isPutty;
	size_t length;

	*stream = NULL;
	if (ssh_stream_alloc(t, url, gitCmd, stream) < 0) {
		giterr_set_oom();
		return -1;
	}

	s = (ssh_stream *)*stream;

	for (i = 0; i < ARRAY_SIZE(ssh_prefixes); ++i) {
		const char *p = ssh_prefixes[i];

		if (!git__prefixcmp(url, p)) {
			if (extract_url_parts(&host, &port, &path, &user, &pass, url, NULL) < 0)
				goto on_error;

			goto post_extract;
		}
	}
	if (git_ssh_extract_url_parts(&host, &user, url) < 0)
		goto on_error;

post_extract:
	if (!ssh)
	{
		giterr_set(GITERR_SSH, "No GIT_SSH tool configured");
		goto on_error;
	}

	isPutty = wcstristr(ssh, L"plink");
	if (port) {
		if (isPutty)
			git_buf_printf(&params, " -P %s", port);
		else
			git_buf_printf(&params, " -p %s", port);
	}
	if (isPutty && !wcstristr(ssh, L"tortoiseplink")) {
		git_buf_puts(&params, " -batch");
	}
	if (user)
		git_buf_printf(&params, " %s@%s ", user, host);
	else
		git_buf_printf(&params, " %s ", host);
	if (gen_proto(&params, s->cmd, s->url))
		goto on_error;
	if (git_buf_oom(&params)) {
		giterr_set_oom();
		goto on_error;
	}

	if (git__utf8_to_16_alloc(&wideParams, params.ptr) < 0) {
		giterr_set_oom();
		goto on_error;
	}
	git_buf_free(&params);

	length = wcslen(ssh) + wcslen(wideParams) + 3;
	cmd = git__calloc(length, sizeof(wchar_t));
	if (!cmd) {
		giterr_set_oom();
		goto on_error;
	}

	wcscat_s(cmd, length, L"\"");
	wcscat_s(cmd, length, ssh);
	wcscat_s(cmd, length, L"\"");
	wcscat_s(cmd, length, wideParams);

	if (command_start(cmd, &s->commandHandle, t->pEnv, isPutty ? CREATE_NEW_CONSOLE : DETACHED_PROCESS))
		goto on_error;

	git__free(wideParams);
	git__free(cmd);
	t->current_stream = s;
	git__free(host);
	git__free(port);
	git__free(path);
	git__free(user);
	git__free(pass);

	return 0;

on_error:
	t->current_stream = NULL;

	if (*stream)
		ssh_stream_free(*stream);

	git_buf_free(&params);

	if (wideParams)
		git__free(wideParams);

	if (cmd)
		git__free(cmd);

	git__free(host);
	git__free(port);
	git__free(user);
	git__free(pass);

	return -1;
}