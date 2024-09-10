char * gvconfig_libdir(GVC_t * gvc)
{
    static char line[BSZ];
    static char *libdir;
    static boolean dirShown = 0; 
    char *tmp;

    if (!libdir) {
        libdir=getenv("GVBINDIR");
	if (!libdir) {
#ifdef WIN32
	    int r;
	    char* s;
		
		MEMORY_BASIC_INFORMATION mbi;
		if (VirtualQuery (&gvconfig_libdir, &mbi, sizeof(mbi)) == 0) {
		agerr(AGERR,"failed to get handle for executable.\n");
		return 0;
	    }
	    r = GetModuleFileName ((HMODULE)mbi.AllocationBase, line, BSZ);
	    if (!r || (r == BSZ)) {
		agerr(AGERR,"failed to get path for executable.\n");
		return 0;
	    }
	    s = strrchr(line,'\\');
	    if (!s) {
		agerr(AGERR,"no slash in path %s.\n", line);
		return 0;
	    }
	    *s = '\0';
	    libdir = line;
#else
	    libdir = GVLIBDIR;	    
#ifdef __APPLE__
	    uint32_t i, c = _dyld_image_count();
	    size_t len, ind;
	    const char* path;
	    for (i = 0; i < c; ++i) {
		path = _dyld_get_image_name(i);
		tmp = strstr(path, "/libgvc.");
		if (tmp) {
		    if (tmp > path) {
			/* Check for real /lib dir. Don't accept pre-install /.libs */
			char* s = tmp-1;
			/* back up to previous slash (or head of string) */
			while ((*s != '/') && (s > path)) s--;
			if (strncmp (s, DOTLIBS, STRLEN(DOTLIBS)) == 0)
			    continue;
		    }

		    ind = tmp - path;  /* byte offset */
		    len = ind + sizeof("/graphviz");
		    if (len < BSZ)
			libdir = line;
		    else
		        libdir = gmalloc(len);
		    bcopy (path, libdir, ind);
		    /* plugins are in "graphviz" subdirectory */
		    strcpy(libdir+ind, "/graphviz");  
		    break;
		}
	    }
#else
	    FILE* f = fopen ("/proc/self/maps", "r");
	    char* path;
	    if (f) {
		while (!feof (f)) {
		    if (!fgets (line, sizeof (line), f))
			continue;
		    if (!strstr (line, " r-xp "))
			continue;
		    path = strchr (line, '/');
		    if (!path)
		        continue;
		    tmp = strstr (path, "/libgvc.");
		    if (tmp) {
			*tmp = 0;
			/* Check for real /lib dir. Don't accept pre-install /.libs */
			if (strcmp(strrchr(path,'/'), "/.libs") == 0)
			    continue;
			strcpy(line, path);  /* use line buffer for result */
			strcat(line, "/graphviz");  /* plugins are in "graphviz" subdirectory */
			libdir = line;
			break;
		    }
		}
		fclose (f);
	    }
#endif
#endif
	}
    }
    if (gvc->common.verbose && !dirShown) {
	fprintf (stderr, "libdir = \"%s\"\n", (libdir ? libdir : "<null>"));
	dirShown = 1;
    }
    return libdir;
}