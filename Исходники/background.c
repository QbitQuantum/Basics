/* Runs command in a background and redirects its stdout and stderr streams to
 * file streams which are set.  Returns (pid_t)0 or (pid_t)-1 on error. */
static pid_t
background_and_capture_internal(char cmd[], int user_sh, FILE **out, FILE **err,
		int out_pipe[2], int err_pipe[2])
{
	wchar_t *args[4];
	char cwd[PATH_MAX];
	int code;
	wchar_t *final_wide_cmd;
	wchar_t *wide_sh = NULL;

	if(_dup2(out_pipe[1], _fileno(stdout)) != 0)
		return (pid_t)-1;
	if(_dup2(err_pipe[1], _fileno(stderr)) != 0)
		return (pid_t)-1;

	cwd[0] = '\0';
	if(get_cwd(cwd, sizeof(cwd)) != NULL)
	{
		if(is_unc_path(cwd))
		{
			(void)chdir(get_tmpdir());
		}
	}

	final_wide_cmd = to_wide(cmd);

	wide_sh = to_wide(user_sh ? cfg.shell : "cmd");
	if(!user_sh || curr_stats.shell_type == ST_CMD)
	{
		args[0] = wide_sh;
		args[1] = L"/C";
		args[2] = final_wide_cmd;
		args[3] = NULL;
	}
	else
	{
		args[0] = wide_sh;
		args[1] = L"-c";
		args[2] = final_wide_cmd;
		args[3] = NULL;
	}

	code = _wspawnvp(P_NOWAIT, args[0], (const wchar_t **)args);

	free(wide_sh);
	free(final_wide_cmd);

	if(is_unc_path(cwd))
	{
		(void)chdir(cwd);
	}

	if(code == 0)
	{
		return (pid_t)-1;
	}

	if((*out = _fdopen(out_pipe[0], "r")) == NULL)
		return (pid_t)-1;
	if((*err = _fdopen(err_pipe[0], "r")) == NULL)
	{
		fclose(*out);
		return (pid_t)-1;
	}

	return 0;
}