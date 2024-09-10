int main(int Argc, char *ARGV[])
{
    ARGS arg;
#define PROG_NAME_SIZE	39
    char pname[PROG_NAME_SIZE+1];
    FUNCTION f,*fp;
    MS_STATIC const char *prompt;
    MS_STATIC char buf[1024];
    char *to_free=NULL;
    int n,i,ret=0;
    int argc;
    char **argv,*p;
    LHASH_OF(FUNCTION) *prog=NULL;
    long errline;

#if defined( OPENSSL_SYS_VMS) && (__INITIAL_POINTER_SIZE == 64)
    /* 2011-03-22 SMS.
     * If we have 32-bit pointers everywhere, then we're safe, and
     * we bypass this mess, as on non-VMS systems.  (See ARGV,
     * above.)
     * Problem 1: Compaq/HP C before V7.3 always used 32-bit
     * pointers for argv[].
     * Fix 1: For a 32-bit argv[], when we're using 64-bit pointers
     * everywhere else, we always allocate and use a 64-bit
     * duplicate of argv[].
     * Problem 2: Compaq/HP C V7.3 (Alpha, IA64) before ECO1 failed
     * to NULL-terminate a 64-bit argv[].  (As this was written, the
     * compiler ECO was available only on IA64.)
     * Fix 2: Unless advised not to (VMS_TRUST_ARGV), we test a
     * 64-bit argv[argc] for NULL, and, if necessary, use a
     * (properly) NULL-terminated (64-bit) duplicate of argv[].
     * The same code is used in either case to duplicate argv[].
     * Some of these decisions could be handled in preprocessing,
     * but the code tends to get even uglier, and the penalty for
     * deciding at compile- or run-time is tiny.
     */
    char **Argv = NULL;
    int free_Argv = 0;

    if ((sizeof( _Argv) < 8)        /* 32-bit argv[]. */
# if !defined( VMS_TRUST_ARGV)
            || (_Argv[ Argc] != NULL)      /* Untrusted argv[argc] not NULL. */
# endif
       )
    {
        int i;
        Argv = OPENSSL_malloc( (Argc+ 1)* sizeof( char *));
        if (Argv == NULL)
        {
            ret = -1;
            goto end;
        }
        for(i = 0; i < Argc; i++)
            Argv[i] = _Argv[i];
        Argv[ Argc] = NULL;     /* Certain NULL termination. */
        free_Argv = 1;
    }
    else
    {
        /* Use the known-good 32-bit argv[] (which needs the
         * type cast to satisfy the compiler), or the trusted or
         * tested-good 64-bit argv[] as-is. */
        Argv = (char **)_Argv;
    }
#endif /* defined( OPENSSL_SYS_VMS) && (__INITIAL_POINTER_SIZE == 64) */

    arg.data=NULL;
    arg.count=0;

    if (bio_err == NULL)
        if ((bio_err=BIO_new(BIO_s_file())) != NULL)
            BIO_set_fp(bio_err,stderr,BIO_NOCLOSE|BIO_FP_TEXT);

    if (getenv("OPENSSL_DEBUG_MEMORY") != NULL) /* if not defined, use compiled-in library defaults */
    {
        if (!(0 == strcmp(getenv("OPENSSL_DEBUG_MEMORY"), "off")))
        {
            CRYPTO_malloc_debug_init();
            CRYPTO_set_mem_debug_options(V_CRYPTO_MDEBUG_ALL);
        }
        else
        {
            /* OPENSSL_DEBUG_MEMORY=off */
            CRYPTO_set_mem_debug_functions(0, 0, 0, 0, 0);
        }
    }
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

#if 0
    if (getenv("OPENSSL_DEBUG_LOCKING") != NULL)
#endif
    {
        CRYPTO_set_locking_callback(lock_dbg_cb);
    }

    if(getenv("OPENSSL_FIPS")) {
#ifdef OPENSSL_FIPS
        if (!FIPS_mode_set(1)) {
            ERR_load_crypto_strings();
            ERR_print_errors(BIO_new_fp(stderr,BIO_NOCLOSE));
            EXIT(1);
        }
#else
        fprintf(stderr, "FIPS mode not supported.\n");
        EXIT(1);
#endif
    }

    apps_startup();

    /* Lets load up our environment a little */
    p=getenv("OPENSSL_CONF");
    if (p == NULL)
        p=getenv("SSLEAY_CONF");
    if (p == NULL)
        p=to_free=make_config_name();

    default_config_file=p;

    config=NCONF_new(NULL);
    i=NCONF_load(config,p,&errline);
    if (i == 0)
    {
        if (ERR_GET_REASON(ERR_peek_last_error())
                == CONF_R_NO_SUCH_FILE)
        {
#if 0 /* ANDROID */
            BIO_printf(bio_err,
                       "WARNING: can't open config file: %s\n",p);
#endif
            ERR_clear_error();
            NCONF_free(config);
            config = NULL;
        }
        else
        {
            ERR_print_errors(bio_err);
            NCONF_free(config);
            exit(1);
        }
    }

    prog=prog_init();

    /* first check the program name */
    program_name(Argv[0],pname,sizeof pname);

    f.name=pname;
    fp=lh_FUNCTION_retrieve(prog,&f);
    if (fp != NULL)
    {
        Argv[0]=pname;
        ret=fp->func(Argc,Argv);
        goto end;
    }

    /* ok, now check that there are not arguments, if there are,
     * run with them, shifting the ssleay off the front */
    if (Argc != 1)
    {
        Argc--;
        Argv++;
        ret=do_cmd(prog,Argc,Argv);
        if (ret < 0) ret=0;
        goto end;
    }

    /* ok, lets enter the old 'OpenSSL>' mode */

    for (;;)
    {
        ret=0;
        p=buf;
        n=sizeof buf;
        i=0;
        for (;;)
        {
            p[0]='\0';
            if (i++)
                prompt=">";
            else	prompt="OpenSSL> ";
            fputs(prompt,stdout);
            fflush(stdout);
            if (!fgets(p,n,stdin))
                goto end;
            if (p[0] == '\0') goto end;
            i=strlen(p);
            if (i <= 1) break;
            if (p[i-2] != '\\') break;
            i-=2;
            p+=i;
            n-=i;
        }
        if (!chopup_args(&arg,buf,&argc,&argv)) break;

        ret=do_cmd(prog,argc,argv);
        if (ret < 0)
        {
            ret=0;
            goto end;
        }
        if (ret != 0)
            BIO_printf(bio_err,"error in %s\n",argv[0]);
        (void)BIO_flush(bio_err);
    }
    BIO_printf(bio_err,"bad exit\n");
    ret=1;
end:
    if (to_free)
        OPENSSL_free(to_free);
    if (config != NULL)
    {
        NCONF_free(config);
        config=NULL;
    }
    if (prog != NULL) lh_FUNCTION_free(prog);
    if (arg.data != NULL) OPENSSL_free(arg.data);

    apps_shutdown();

    CRYPTO_mem_leaks(bio_err);
    if (bio_err != NULL)
    {
        BIO_free(bio_err);
        bio_err=NULL;
    }
#if defined( OPENSSL_SYS_VMS) && (__INITIAL_POINTER_SIZE == 64)
    /* Free any duplicate Argv[] storage. */
    if (free_Argv)
    {
        OPENSSL_free(Argv);
    }
#endif
    OPENSSL_EXIT(ret);
}