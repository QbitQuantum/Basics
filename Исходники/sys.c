static enum MqErrorE SysServerSpawn (
    struct MqS * const context,
    char * * argv,
    MQ_CST  name,
    struct MqIdS * idP
)
{
    pid_t pid;
    int err=0;

    // spawn setup !before! a spawn is created
    if (context->setup.fSpawnInit) (*context->setup.fSpawnInit)(context);

    // perl !need! sigschiled enabled at startup make it the default

#if defined(HAVE_POSIX_SPAWN)
    {
        posix_spawnattr_t sa;
        if ((err=posix_spawnattr_init(&sa)) != 0) {
            goto error;
        }
        if (unlikely ((err=posix_spawnp(&pid, name, NULL, &sa, (char *const *) argv, __environ)) != 0)) {
            posix_spawnattr_destroy(&sa);
            goto error;
        }
        if ((err=posix_spawnattr_destroy(&sa)) != 0) {
            goto error;
        }
    }
    goto ok;

#elif (defined(HAVE_FORK) || defined(HAVE_VFORK))  && defined(HAVE_EXECVP)
//#if (defined(HAVE_FORK) || defined(HAVE_VFORK))  && defined(HAVE_EXECVP)

    // fork to create the child
#if defined(HAVE_VFORK)
    if (unlikely ((pid = vfork()) == -1)) goto error;
#elif defined(HAVE_FORK)
    if (unlikely ((pid = MqSysFork()) == -1)) goto error;
#else
    goto error;
#endif

    if (pid == 0) {
        // this is the child
        if (execvp(name, argv) == -1) {
            _exit (EXIT_FAILURE);
        }
        // the child will never reach this
    }
    goto ok;

#elif defined(MQ_IS_WIN32)
    char buf[2048];
    char *nbuf=buf;

    // build command-line
    for (; *argv != '\0'; argv++) {
        nbuf += sprintf(nbuf, "\"%s\" ", *argv);
    }

    // start process
    if (unlikely ((pid = _spawnlp (_P_NOWAIT, name, buf, NULL)) == -1)) {
        //printC(strerror(errno))
        goto error;
    }
    goto ok;

#else
# error unable to SysServerSpawn
#endif

ok:
    (*idP).val = (mqpid_t)pid;
    (*idP).type = MQ_ID_PROCESS;
    return MQ_OK;

error:
    MqErrorDbV (MQ_ERROR_CAN_NOT_START_SERVER, name);
    if (err != 0) {
        MqErrorSysAppend (__func__, err);
    }
    return MqErrorGetCodeI(context);
}