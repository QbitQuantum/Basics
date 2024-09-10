void
ruby_init_loadpath_safe(int safe_level, const char* szRoot)
{
    VALUE load_path;
#if defined LOAD_RELATIVE
    char libpath[MAXPATHLEN + 1];
    char *p;
    int rest;
	if ( szRoot )
		strncpy(libpath, szRoot, sizeof(libpath) - 1);
	else
	{
#if defined _WIN32 || defined __CYGWIN__
    GetModuleFileNameA(libruby, libpath, sizeof libpath);
#elif defined(__EMX__)
    _execname(libpath, sizeof(libpath) - 1);
#endif
	}
//RHO
    libpath[sizeof(libpath) - 1] = '\0';
#if defined DOSISH
    translate_char(libpath, '\\', '/');
#elif defined __CYGWIN__
    {
	char rubylib[FILENAME_MAX];
	cygwin_conv_to_posix_path(libpath, rubylib);
	strncpy(libpath, rubylib, sizeof(libpath));
    }
#endif
    p = strrchr(libpath, '/');
    if (p) {
	*p = 0;
	if (p - libpath > 3 && !STRCASECMP(p - 4, "/bin")) {
	    p -= 4;
	    *p = 0;
	}
    }
    else {
	strcpy(libpath, ".");
	p = libpath + 1;
    }

    rest = sizeof(libpath) - 1 - (p - libpath);

#define RUBY_RELATIVE(path) (strncpy(p, (path), rest), libpath)
#else
#define RUBY_RELATIVE(path) (path)
#endif
#define incpush(path) rb_ary_push(load_path, rubylib_mangled_path2(path))
    load_path = GET_VM()->load_path;
//RHO
    incpush(RUBY_RELATIVE(RUBY_LIB));
    incpush(RUBY_RELATIVE(RUBY_SITE_LIB));
    incpush(RUBY_RELATIVE(RUBY_SITE_LIB2));
/*
    if (safe_level == 0) {
	ruby_push_include(getenv("RUBYLIB"), identical_path);
    }

#ifdef RUBY_SEARCH_PATH
    incpush(RUBY_RELATIVE(RUBY_SEARCH_PATH));
#endif

    incpush(RUBY_RELATIVE(RUBY_SITE_LIB2));
#ifdef RUBY_SITE_THIN_ARCHLIB
    incpush(RUBY_RELATIVE(RUBY_SITE_THIN_ARCHLIB));
#endif
    incpush(RUBY_RELATIVE(RUBY_SITE_ARCHLIB));
    incpush(RUBY_RELATIVE(RUBY_SITE_LIB));

    incpush(RUBY_RELATIVE(RUBY_VENDOR_LIB2));
#ifdef RUBY_VENDOR_THIN_ARCHLIB
    incpush(RUBY_RELATIVE(RUBY_VENDOR_THIN_ARCHLIB));
#endif
    incpush(RUBY_RELATIVE(RUBY_VENDOR_ARCHLIB));
    incpush(RUBY_RELATIVE(RUBY_VENDOR_LIB));

    incpush(RUBY_RELATIVE(RUBY_LIB));
#ifdef RUBY_THIN_ARCHLIB
    incpush(RUBY_RELATIVE(RUBY_THIN_ARCHLIB));
#endif
    incpush(RUBY_RELATIVE(RUBY_ARCHLIB));

    if (safe_level == 0) {
	incpush(".");
    }
*/
//RHO
}