void RNG_SystemInfoForRNG(void)
{
    FILE *fp;
    char buf[BUFSIZ];
    size_t bytes;
    const char * const *cp;
    char *randfile;
#ifdef DARWIN
#if TARGET_OS_IPHONE
    /* iOS does not expose a way to access environ. */
    char **environ = NULL;
#else
    char **environ = *_NSGetEnviron();
#endif
#else
    extern char **environ;
#endif
#ifdef BEOS
    static const char * const files[] = {
	"/boot/var/swap",
	"/boot/var/log/syslog",
	"/boot/var/tmp",
	"/boot/home/config/settings",
	"/boot/home",
	0
    };
#else
    static const char * const files[] = {
	"/etc/passwd",
	"/etc/utmp",
	"/tmp",
	"/var/tmp",
	"/usr/tmp",
	0
    };
#endif

#if defined(BSDI)
    static char netstat_ni_cmd[] = "netstat -nis";
#else
    static char netstat_ni_cmd[] = "netstat -ni";
#endif

    GiveSystemInfo();

    bytes = RNG_GetNoise(buf, sizeof(buf));
    RNG_RandomUpdate(buf, bytes);

    /*
     * Pass the C environment and the addresses of the pointers to the
     * hash function. This makes the random number function depend on the
     * execution environment of the user and on the platform the program
     * is running on.
     */
    if (environ != NULL) {
        cp = (const char * const *) environ;
        while (*cp) {
	    RNG_RandomUpdate(*cp, strlen(*cp));
	    cp++;
        }
        RNG_RandomUpdate(environ, (char*)cp - (char*)environ);
    }

    /* Give in system information */
    if (gethostname(buf, sizeof(buf)) == 0) {
	RNG_RandomUpdate(buf, strlen(buf));
    }
    GiveSystemInfo();

    /* grab some data from system's PRNG before any other files. */
    bytes = RNG_FileUpdate("/dev/urandom", SYSTEM_RNG_SEED_COUNT);

    /* If the user points us to a random file, pass it through the rng */
    randfile = getenv("NSRANDFILE");
    if ( ( randfile != NULL ) && ( randfile[0] != '\0') ) {
	char *randCountString = getenv("NSRANDCOUNT");
	int randCount = randCountString ? atoi(randCountString) : 0;
	if (randCount != 0) {
	    RNG_FileUpdate(randfile, randCount);
	} else {
	    RNG_FileForRNG(randfile);
	}
    }

    /* pass other files through */
    for (cp = files; *cp; cp++)
	RNG_FileForRNG(*cp);

/*
 * Bug 100447: On BSD/OS 4.2 and 4.3, we have problem calling safe_popen
 * in a pthreads environment.  Therefore, we call safe_popen last and on
 * BSD/OS we do not call safe_popen when we succeeded in getting data
 * from /dev/urandom.
 *
 * Bug 174993: On platforms providing /dev/urandom, don't fork netstat
 * either, if data has been gathered successfully.
 */

#if defined(BSDI) || defined(FREEBSD) || defined(NETBSD) \
    || defined(OPENBSD) || defined(DARWIN) || defined(LINUX) \
    || defined(HPUX)
    if (bytes)
        return;
#endif

#ifdef SOLARIS

/*
 * On Solaris, NSS may be initialized automatically from libldap in
 * applications that are unaware of the use of NSS. safe_popen forks, and
 * sometimes creates issues with some applications' pthread_atfork handlers.
 * We always have /dev/urandom on Solaris 9 and above as an entropy source,
 * and for Solaris 8 we have the libkstat interface, so we don't need to
 * fork netstat.
 */

#undef DO_NETSTAT
    if (!bytes) {
        /* On Solaris 8, /dev/urandom isn't available, so we use libkstat. */
        PRUint32 kstat_bytes = 0;
        if (SECSuccess != RNG_kstat(&kstat_bytes)) {
            PORT_Assert(0);
        }
        bytes += kstat_bytes;
        PORT_Assert(bytes);
    }
#endif

#ifdef DO_NETSTAT
    fp = safe_popen(netstat_ni_cmd);
    if (fp != NULL) {
	while ((bytes = fread(buf, 1, sizeof(buf), fp)) > 0)
	    RNG_RandomUpdate(buf, bytes);
	safe_pclose(fp);
    }
#endif

}