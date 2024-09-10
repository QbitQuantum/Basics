/* _unix_get_executable_name:
 *  Return full path to the current executable, use proc fs if available.
 */
void get_executable_name(char *output, int size)
{
#ifdef ALLEGRO_HAVE_SV_PROCFS
	struct prpsinfo psinfo;
	int fd;
#endif
#if defined ALLEGRO_HAVE_SV_PROCFS || defined ALLEGRO_SYS_GETEXECNAME
	char *s;
#endif
	char linkname[1024];
	char filename[1024];
	struct stat finfo;
	FILE *pipe;
	pid_t pid;
	int len;

#ifdef ALLEGRO_HAVE_GETEXECNAME
	s = getexecname();
	if (s) {
		if (s[0] == '/') {   /* Absolute path */
			strncpy(output, s, size);
			output[size - 1] = 0;
			return;
		}
		else {               /* Not an absolute path */
			if (_find_executable_file(s, output, size))
				return;
		}
	}
	s = NULL;
#endif

	/* We need the PID in order to query procfs */
	pid = getpid();

	/* Try a Linux-like procfs */
	/* get symolic link to executable from proc fs */
	sprintf (linkname, "/proc/%d/exe", pid);
	if (stat (linkname, &finfo) == 0) {
		len = readlink (linkname, filename, sizeof(filename)-1);
		if (len>-1) {
			filename[len] = '\0';

			strncpy(output, filename, size);
			output[size - 1] = 0;
			return;
		}
   }

   /* Use System V procfs calls if available */
#ifdef ALLEGRO_HAVE_SV_PROCFS
	sprintf (linkname, "/proc/%d/exe", pid);
	fd = open(linkname, O_RDONLY);
	if (fd >= 0) {
		ioctl(fd, PIOCPSINFO, &psinfo);
		close(fd);

		/* Use argv[0] directly if we can */
#ifdef ALLEGRO_HAVE_PROCFS_ARGCV
	if (psinfo.pr_argv && psinfo.pr_argc) {
		if (_find_executable_file(psinfo.pr_argv[0], output, size))
			return;
	}
	else
#endif
	{
		/* Emulate it */
		/* We use the pr_psargs field to find argv[0]
		 * This is better than using the pr_fname field because we need
		 * the additional path information that may be present in argv[0]
		*/

		/* Skip other args */
		s = strchr(psinfo.pr_psargs, ' ');
		if (s) s[0] = '\0';
		if (_find_executable_file(psinfo.pr_psargs, output, size))
			 return;
	}

	/* Try the pr_fname just for completeness' sake if argv[0] fails */
	if (_find_executable_file(psinfo.pr_fname, output, size))
		return;
	}
#endif

	/* Last resort: try using the output of the ps command to at least find */
	/* the name of the file if not the full path */
	sprintf (filename, "ps -p %d", pid);
	pipe = popen(filename, "r");
	if (pipe) {
		/* The first line of output is a header */
		const char* result = fgets(linkname, sizeof(linkname), pipe);
		if (!result) linkname[0] = 0;

		/* The information we want is in the last column; find it */
		len = strlen(linkname);
		while (linkname[len] != ' ' && linkname[len] != '\t')
			len--;

		/* The second line contains the info we want */
		result = fgets(linkname, sizeof(linkname), pipe);
		if (!result) { linkname[0] = 0; len = 0; }
		pclose(pipe);

		/* Treat special cases: filename between [] and - for login shell */
		if (linkname[len] == '-')
			len++;

		/* Now, the filename should be in the last column */
		strcpy(filename, linkname+len+1);

		if (_find_executable_file(filename, output, size))
			return;

		/* Just return the output from ps... */
		strncpy(output, filename, size);
		output[size - 1] = 0;
		return;
	}

#ifdef ALLEGRO_WITH_MAGIC_MAIN
	/* Try the captured argv[0] */
	if (_find_executable_file(__crt0_argv[0], output, size))
		return;
#endif

	/* Give up; return empty string */
	if (size > 0)
		*output = '\0';
}