int main ( int argc, char **argv, char **env )
{
    int i;
    char *stmpdir;
    char *buf = (char *)malloc(MAXPATHLEN);
#ifdef WIN32
typedef BOOL (WINAPI *pALLOW)(DWORD);
    HINSTANCE hinstLib;
    pALLOW ProcAdd;
#ifndef ASFW_ANY
#define ASFW_ANY -1
#endif
#endif

    par_init_env();
    par_mktmpdir( argv );

    stmpdir = (char *)par_getenv("PAR_TEMP");
    if ( stmpdir != NULL ) {
        i = mkdir(stmpdir, 0755);
        if ( (i != 0) && (i != EEXIST) && (i != -1) ) {
            fprintf(stderr, "%s: creation of private temporary subdirectory %s failed - aborting with %i.\n", argv[0], stmpdir, errno);
            return 2;
        }
    }

    i = my_mkfile( argv[0], stmpdir, name_load_me_0, size_load_me_0 );
    if ( !i ) return 2;
    if ( i != -2 ) {
        WRITE_load_me_0(i);
        close(i); chmod(my_file, 0755);
    }

    my_file = par_basename(par_findprog(argv[0], strdup(par_getenv("PATH"))));

    i = my_mkfile( argv[0], stmpdir, my_file, size_load_me_1 );
    if ( !i ) return 2;
    if ( i != -2 ) {
        WRITE_load_me_1(i);
        close(i); chmod(my_file, 0755);
    }

    sprintf(buf, "%i", argc);
    par_setenv("PAR_ARGC", buf);
    for (i = 0; i < argc; i++) {
        buf = (char *)malloc(strlen(argv[i]) + 14);
        sprintf(buf, "PAR_ARGV_%i", i);
        par_setenv(buf, argv[i]);
    }

#ifdef WIN32
    hinstLib = LoadLibrary("user32");
    if (hinstLib != NULL) {
        ProcAdd = (pALLOW) GetProcAddress(hinstLib, "AllowSetForegroundWindow");
        if (ProcAdd != NULL)
        {
            (ProcAdd)(ASFW_ANY);
        }
    }

    par_setenv("PAR_SPAWNED", "1");
    i = spawnvpe(P_WAIT, my_file, (const char* const*)argv, (const char* const*)environ);
#else
    execvp(my_file, argv);
    return 2;
#endif

    par_cleanup(stmpdir);
    return i;
}