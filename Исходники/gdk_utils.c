int
GDKinit(opt *set, int setlen)
{
	char *dbpath = mo_find_option(set, setlen, "gdk_dbpath");
	char *p;
	opt *n;
	int i, j, nlen = 0;
	char buf[16];

	/* some sanity checks (should also find if symbols are not defined) */
	assert(sizeof(char) == SIZEOF_CHAR);
	assert(sizeof(short) == SIZEOF_SHORT);
	assert(sizeof(int) == SIZEOF_INT);
	assert(sizeof(long) == SIZEOF_LONG);
	assert(sizeof(lng) == SIZEOF_LNG);
	assert(sizeof(oid) == SIZEOF_OID);
	assert(sizeof(void *) == SIZEOF_VOID_P);
	assert(sizeof(wrd) == SIZEOF_WRD);
	assert(sizeof(size_t) == SIZEOF_SIZE_T);
	assert(sizeof(ptrdiff_t) == SIZEOF_PTRDIFF_T);
	assert(SIZEOF_OID == SIZEOF_INT || SIZEOF_OID == SIZEOF_LNG);

#ifdef NEED_MT_LOCK_INIT
	MT_lock_init(&MT_system_lock,"MT_system_lock");
	ATOMIC_INIT(GDKstoppedLock, "GDKstoppedLock");
	ATOMIC_INIT(mbyteslock, "mbyteslock");
	MT_lock_init(&GDKnameLock, "GDKnameLock");
	MT_lock_init(&GDKthreadLock, "GDKthreadLock");
	MT_lock_init(&GDKtmLock, "GDKtmLock");
#endif
	for (i = 0; i <= BBP_BATMASK; i++) {
		MT_lock_init(&GDKbatLock[i].swap, "GDKswapLock");
		MT_lock_init(&GDKbatLock[i].hash, "GDKhashLock");
		MT_lock_init(&GDKbatLock[i].imprints, "GDKimprintsLock");
	}
	for (i = 0; i <= BBP_THREADMASK; i++) {
		MT_lock_init(&GDKbbpLock[i].alloc, "GDKcacheLock");
		MT_lock_init(&GDKbbpLock[i].trim, "GDKtrimLock");
		GDKbbpLock[i].free = 0;
	}
	errno = 0;
	if (!GDKenvironment(dbpath))
		return 0;

	if ((p = mo_find_option(set, setlen, "gdk_debug")))
		GDKdebug = strtol(p, NULL, 10);

	if ((p = mo_find_option(set, setlen, "gdk_mem_pagebits")))
		GDK_mem_pagebits = (int) strtol(p, NULL, 10);

	mnstr_init();
	MT_init_posix();
	THRinit();
#ifndef NATIVE_WIN32
	BATSIGinit();
#endif
#ifdef WIN32
	(void) signal(SIGABRT, BATSIGabort);
	_set_abort_behavior(0, _CALL_REPORTFAULT | _WRITE_ABORT_MSG);
	_set_error_mode(_OUT_TO_STDERR);
#endif
	GDKlockHome();

	/* Mserver by default takes 80% of all memory as a default */
	GDK_mem_maxsize = GDK_mem_maxsize_max = (size_t) ((double) MT_npages() * (double) MT_pagesize() * 0.815);
#ifdef NATIVE_WIN32
	GDK_mmap_minsize = GDK_mem_maxsize_max;
#else
	GDK_mmap_minsize = MIN( 1<<30 , GDK_mem_maxsize_max/6 );
	/*   per op:  2 args + 1 res, each with head & tail  =>  (2+1)*2 = 6  ^ */
#endif
	GDK_mem_bigsize = 1024*1024;
	GDKremovedir(DELDIR);
	BBPinit();

	HEAPcacheInit();

	GDKkey = BATnew(TYPE_void, TYPE_str, 100);
	GDKval = BATnew(TYPE_void, TYPE_str, 100);
	if (GDKkey == NULL)
		GDKfatal("GDKinit: Could not create environment BAT");
	if (GDKval == NULL)
		GDKfatal("GDKinit: Could not create environment BAT");
	BATseqbase(GDKkey,0);
	BATkey(GDKkey, BOUND2BTRUE);
	BATrename(GDKkey, "environment_key");
	BATmode(GDKkey, TRANSIENT);

	BATseqbase(GDKval,0);
	BATkey(GDKval, BOUND2BTRUE);
	BATrename(GDKval, "environment_val");
	BATmode(GDKval, TRANSIENT);

	n = (opt *) malloc(setlen * sizeof(opt));
	for (i = 0; i < setlen; i++) {
		int done = 0;

		for (j = 0; j < nlen; j++) {
			if (strcmp(n[j].name, set[i].name) == 0) {
				if (n[j].kind < set[i].kind) {
					n[j] = set[i];
				}
				done = 1;
				break;
			}
		}
		if (!done) {
			n[nlen] = set[i];
			nlen++;
		}
	}
	for (i = 0; i < nlen; i++)
		GDKsetenv(n[i].name, n[i].value);
	free(n);

	if ((p = GDKgetenv("gdk_dbpath")) != NULL &&
	    (p = strrchr(p, DIR_SEP)) != NULL) {
		GDKsetenv("gdk_dbname", p + 1);
#if DIR_SEP != '/'		/* on Windows look for different separator */
	} else if ((p = GDKgetenv("gdk_dbpath")) != NULL &&
	    (p = strrchr(p, '/')) != NULL) {
		GDKsetenv("gdk_dbname", p + 1);
#endif
	}
	if ((p = GDKgetenv("gdk_mem_maxsize"))) {
		GDK_mem_maxsize = MAX(1 << 26, (size_t) strtoll(p, NULL, 10));
	}
	if ((p = GDKgetenv("gdk_vm_maxsize"))) {
		GDK_vm_maxsize = MAX(1 << 30, (size_t) strtoll(p, NULL, 10));
	}
	if ((p = GDKgetenv("gdk_mem_bigsize"))) {
		/* when allocating >6% of all RAM; do so using
		 * vmalloc() iso malloc() */
		lng max_mem_bigsize = GDK_mem_maxsize_max / 16;

		/* sanity check to avoid memory fragmentation */
		GDK_mem_bigsize = (size_t) MIN(max_mem_bigsize, strtoll(p, NULL, 10));
	}
	if ((p = GDKgetenv("gdk_mmap_minsize"))) {
		GDK_mmap_minsize = MAX(REMAP_PAGE_MAXSIZE, (size_t) strtoll(p, NULL, 10));
	}
	if (GDKgetenv("gdk_mem_pagebits") == NULL) {
		snprintf(buf, sizeof(buf), "%d", GDK_mem_pagebits);
		GDKsetenv("gdk_mem_pagebits", buf);
	}
	if (GDKgetenv("gdk_mem_bigsize") == NULL) {
		snprintf(buf, sizeof(buf), SZFMT, GDK_mem_bigsize);
		GDKsetenv("gdk_mem_bigsize", buf);
	}
	if (GDKgetenv("monet_pid") == NULL) {
		snprintf(buf, sizeof(buf), "%d", (int) getpid());
		GDKsetenv("monet_pid", buf);
	}

	GDKnr_threads = GDKgetenv_int("gdk_nr_threads", 0);
	if (GDKnr_threads == 0)
		GDKnr_threads = MT_check_nr_cores();
#ifdef NATIVE_WIN32
	GDK_mmap_minsize /= (GDKnr_threads ? GDKnr_threads : 1);
#else
	/* WARNING: This unconditionally overwrites above settings, */
	/* incl. setting via MonetDB env. var. "gdk_mmap_minsize" ! */
	GDK_mmap_minsize = MIN( 1<<30 , (GDK_mem_maxsize_max/6) / (GDKnr_threads ? GDKnr_threads : 1) );
	/*    per op:  2 args + 1 res, each with head & tail  =>  (2+1)*2 = 6  ^ */
#endif

	if ((p = mo_find_option(set, setlen, "gdk_vmtrim")) == NULL ||
	    strcasecmp(p, "yes") == 0)
		MT_create_thread(&GDKvmtrim_id, GDKvmtrim, &GDK_mem_maxsize,
				 MT_THR_JOINABLE);

	return 1;
}