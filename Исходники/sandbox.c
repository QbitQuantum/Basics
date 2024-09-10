R_API int r_sandbox_system (const char *x, int n) {
	if (enabled) {
		eprintf ("sandbox: system call disabled\n");
		return -1;
	}
#if LIBC_HAVE_FORK
#if LIBC_HAVE_SYSTEM
	if (n) {
#if APPLE_SDK_IPHONEOS
#include <dlfcn.h>
		int (*__system)(const char *cmd)
			= dlsym (NULL, "system");
		if (__system) {
			return __system (x);
		}
		return -1;
#else
		return system (x);
#endif
	}
	return execl ("/bin/sh", "sh", "-c", x, (const char*)NULL);
#else
	#include <spawn.h>
	if (n && !strchr (x, '|')) {
		char **argv, *cmd = strdup (x);
		int rc, pid, argc;
		char *isbg = strchr (cmd, '&');
		// XXX this is hacky
		if (isbg) {
			*isbg = 0;
		}
		argv = r_str_argv (cmd, &argc);
		if (argv) {
			char *argv0 = r_file_path (argv[0]);
			if (!argv0) {
				eprintf ("Cannot find '%s'\n", argv[0]);
				return -1;
			}
			pid = 0;
			posix_spawn (&pid, argv0, NULL, NULL, argv, NULL);
			if (isbg) {
				// XXX. wait for children
				rc = 0;
			} else {
				rc = waitpid (pid, NULL, 0);
			}
			r_str_argv_free (argv);
			free (argv0);
			return rc;
		}
		eprintf ("Error parsing command arguments\n");
		return -1;
	}
	int child = fork();
	if (child == -1) return -1;
	if (child) {
		return waitpid (child, NULL, 0);
	}
	execl ("/bin/sh", "sh", "-c", x, (const char*)NULL);
	exit (1);
#endif
#endif
	return -1;
}