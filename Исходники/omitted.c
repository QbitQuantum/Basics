static pid_t
runve(int mode, const char* path, char* const* argv, char* const* envv)
{
	register char*	s;
	register char**	p;
	register char**	v;

	void*		m1;
	void*		m2;
	pid_t		pid;
	int		oerrno;
	int		ux;
	int		n;
#if defined(_P_DETACH) && defined(_P_NOWAIT)
	int		pgrp;
#endif
#if CONVERT
	char*		d;
	char*		t;
	int		m;
#endif
	struct stat	st;
	char		buf[PATH_MAX];
	char		tmp[PATH_MAX];

#if DEBUG
	static int	trace;
#endif

#if defined(_P_DETACH) && defined(_P_NOWAIT)
	if (mode == _P_DETACH)
	{
		/*
		 * 2004-02-29 cygwin _P_DETACH is useless:
		 *	spawn*() returns 0 instead of the spawned pid
		 *	spawned { pgid sid } are the same as the parent
		 */

		mode = _P_NOWAIT;
		pgrp = 1;
	}
	else
		pgrp = 0;
#endif
	if (!envv)
		envv = (char* const*)environ;
	m1 = m2 = 0;
	oerrno = errno;
#if DEBUG
	if (!trace)
		trace = (s = getenv("_AST_exec_trace")) ? *s : 'n';
#endif
	if (execrate(path, buf, sizeof(buf), 0))
	{
		if (!_stat(buf, &st))
			path = (const char*)buf;
		else
			errno = oerrno;
	}
	if (path != (const char*)buf && _stat(path, &st))
		return -1;
	if (!S_ISREG(st.st_mode) || !(st.st_mode & (S_IXUSR|S_IXGRP|S_IXOTH)))
	{
		errno = EACCES;
		return -1;
	}
	if (magic(path, &ux))
	{
#if _CYGWIN_fork_works
		errno = ENOEXEC;
		return -1;
#else
		ux = 1;
		p = (char**)argv;
		while (*p++);
		if (!(v = (char**)malloc((p - (char**)argv + 2) * sizeof(char*))))
		{
			errno = EAGAIN;
			return -1;
		}
		m1 = v;
		p = v;
		*p++ = (char*)path;
		*p++ = (char*)path;
		path = (const char*)pathshell();
		if (*argv)
			argv++;
		while (*p++ = (char*)*argv++);
		argv = (char* const*)v;
#endif
	}

	/*
	 * the win32 dll search order is
	 *	(1) the directory of path
	 *	(2) .
	 *	(3) /c/(WINNT|WINDOWS)/system32 /c/(WINNT|WINDOWS)
	 *	(4) the directories on $PATH
	 * there are no cygwin dlls in (3), so if (1) and (2) fail
	 * to produce the required dlls its up to (4)
	 *
	 * the standard allows PATH to be anything once the path
	 * to an executable is determined; this code ensures that PATH
	 * contains /bin so that at least the cygwin dll, required
	 * by all cygwin executables, will be found
	 */

	if (p = (char**)envv)
	{
		n = 1;
		while (s = *p++)
			if (strneq(s, "PATH=", 5))
			{
				s += 5;
				do
				{
					s = pathcat(tmp, s, ':', NiL, "");
					if (streq(tmp, "/usr/bin/") || streq(tmp, "/bin/"))
					{
						n = 0;
						break;
					}
				} while (s);
				if (n)
				{
					n = 0;
					snprintf(tmp, sizeof(tmp), "%s:/bin", *(p - 1));
					*(p - 1) = tmp;
				}
				break;
			}
		if (n)
		{
			n = p - (char**)envv + 1;
			p = (char**)envv;
			if (v = (char**)malloc(n * sizeof(char*)))
			{
				m2 = v;
				envv = (char* const*)v;
				*v++ = strcpy(tmp, "PATH=/bin");
				while (*v++ = *p++);
			}
		}
#if CONVERT
		if (!ux && (d = getenv(convertvars[0])))
			for (p = (char**)envv; s = *p; p++)
				if ((n = convert(d, s)) && (m = cygwin_posix_to_win32_path_list_buf_size(s + n)) > 0)
				{
					if (!(t = malloc(n + m + 1)))
						break;
					*p = t;
					memcpy(t, s, n);
					cygwin_posix_to_win32_path_list(s + n, t + n);
				}
#endif
	}

#if DEBUG
	if (trace == 'a' || trace == 'e')
	{
		sfprintf(sfstderr, "%s %s [", mode == _P_OVERLAY ? "_execve" : "_spawnve", path);
		for (n = 0; argv[n]; n++)
			sfprintf(sfstderr, " '%s'", argv[n]);
		if (trace == 'e')
		{
			sfprintf(sfstderr, " ] [");
			for (n = 0; envv[n]; n++)
				sfprintf(sfstderr, " '%s'", envv[n]);
		}
		sfprintf(sfstderr, " ]\n");
		sfsync(sfstderr);
	}
#endif
#if _lib_spawn_mode
	if (mode != _P_OVERLAY)
	{
		pid = _spawnve(mode, path, argv, envv);
#if defined(_P_DETACH) && defined(_P_NOWAIT)
		if (pid > 0 && pgrp)
			setpgid(pid, 0);
#endif
	}
	else
#endif
	{
#if defined(_P_DETACH) && defined(_P_NOWAIT)
		if (pgrp)
			setpgid(0, 0);
#endif
		pid = _execve(path, argv, envv);
	}
	if (m1)
		free(m1);
	if (m2)
		free(m2);
	return pid;
}