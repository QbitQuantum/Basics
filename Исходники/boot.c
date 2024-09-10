int main ( int argc, char **argv, char **env )
{
    int rc, i;
    char *stmpdir;
    embedded_file_t *emb_file;
    char *my_file;
    char *my_perl;
    char *my_prog;
    char buf[20];	/* must be large enough to hold "PAR_ARGV_###" */
#ifdef WIN32
typedef BOOL (WINAPI *pALLOW)(DWORD);
    HINSTANCE hinstLib;
    pALLOW ProcAdd;
#ifndef ASFW_ANY
#define ASFW_ANY -1
#endif
#endif

#define DIE exit(255)

    par_init_env();

    stmpdir = par_mktmpdir( argv );	
    if ( !stmpdir ) DIE;        /* error message has already been printed */

    rc = my_mkdir(stmpdir, 0700);
    if ( rc == -1 && errno != EEXIST) {
	fprintf(stderr, "%s: creation of private cache subdirectory %s failed (errno= %i)\n", 
                        argv[0], stmpdir, errno);
 	DIE;
    }

    /* extract embedded_files[0] (i.e. the custom Perl interpreter) 
     * into stmpdir (but under the same basename as argv[0]) */
    my_prog = par_findprog(argv[0], strdup(par_getenv("PATH")));
    rc = extract_embedded_file(embedded_files, par_basename(my_prog), stmpdir, &my_perl);
    if (rc == EXTRACT_FAIL) {
        fprintf(stderr, "%s: extraction of %s (custom Perl interpreter) failed (errno=%i)\n", 
                            argv[0], my_perl, errno);
        DIE;
    }

    if (rc == EXTRACT_OK)       /* i.e. file didn't already exist */
    {
#ifdef __hpux
        {
            /* HPUX will only honour SHLIB_PATH if the executable is specially marked */
            char *chatr_cmd = malloc(strlen(my_perl) + 200);
            sprintf(chatr_cmd, "/usr/bin/chatr +s enable %s > /dev/null", my_perl);
            system(chatr_cmd);
        }
#endif
#ifdef WIN32
        {
            /* copy IMAGE_OPTIONAL_HEADER.Subsystem  (GUI vs console)
             * from this executable to the just extracted my_perl
             */
            int fd;
            WORD subsystem;

            fd = open(my_prog, O_RDONLY | OPEN_O_BINARY, 0755);
            ASSERT(fd != -1, "open my_prog");
            seek_to_subsystem(fd);
            read(fd, &subsystem, 2);    // CHECK == 2
            close(fd);                  // CHECK != -1

            fd = open(my_perl, O_RDWR | OPEN_O_BINARY, 0755);
            ASSERT(fd != -1, "open my_perl");
            seek_to_subsystem(fd);
            write(fd, &subsystem, 2);   // CHECK == 2
            close(fd);                  // CHECK != -1
        }
#endif
    }

    /* extract the rest of embedded_files into stmpdir */
    emb_file = embedded_files + 1;
    while (emb_file->name) {
        if (extract_embedded_file(emb_file, emb_file->name, stmpdir, &my_file) == EXTRACT_FAIL) {
            fprintf(stderr, "%s: extraction of %s failed (errno=%i)\n", 
                                argv[0], my_file, errno);
            DIE;
        }
        emb_file++;
    }

    /* save original argv[] into environment variables PAR_ARGV_# */
    sprintf(buf, "%i", argc);
    par_setenv("PAR_ARGC", buf);
    for (i = 0; i < argc; i++) {
        sprintf(buf, "PAR_ARGV_%i", i);
        par_unsetenv(buf);
        par_setenv(buf, argv[i]);
    }

    /* finally spawn the custom Perl interpreter */
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
    rc = spawnvpe(P_WAIT, my_perl, (const char* const*)argv, (const char* const*)environ);

    par_cleanup(stmpdir);
    exit(rc);
#else
    execvp(my_perl, argv);
    DIE;
#endif
}