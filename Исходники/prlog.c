void _PR_InitLog(void)
{
    char *ev;

    _pr_logLock = PR_NewLock();

    ev = PR_GetEnv("NSPR_LOG_MODULES");
    if (ev && ev[0]) {
        char module[64];  /* Security-Critical: If you change this
                           * size, you must also change the sscanf
                           * format string to be size-1.
                           */
        PRBool isSync = PR_FALSE;
        PRIntn evlen = strlen(ev), pos = 0;
        PRInt32 bufSize = DEFAULT_BUF_SIZE;
        while (pos < evlen) {
            PRIntn level = 1, count = 0, delta = 0;
            count = sscanf(&ev[pos], "%63[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-]%n:%d%n",
                           module, &delta, &level, &delta);
            pos += delta;
            if (count == 0) break;

            /*
            ** If count == 2, then we got module and level. If count
            ** == 1, then level defaults to 1 (module enabled).
            */
            if (strcasecmp(module, "sync") == 0) {
                isSync = PR_TRUE;
            } else if (strcasecmp(module, "bufsize") == 0) {
                if (level >= LINE_BUF_SIZE) {
                    bufSize = level;
                }
            } else if (strcasecmp(module, "timestamp") == 0) {
                outputTimeStamp = PR_TRUE;
            } else {
                PRLogModuleInfo *lm = logModules;
                PRBool skip_modcheck =
                    (0 == strcasecmp (module, "all")) ? PR_TRUE : PR_FALSE;

                while (lm != NULL) {
                    if (skip_modcheck) lm -> level = (PRLogModuleLevel)level;
                    else if (strcasecmp(module, lm->name) == 0) {
                        lm->level = (PRLogModuleLevel)level;
                        break;
                    }
                    lm = lm->next;
                }
            }
            /*found:*/
            count = sscanf(&ev[pos], " , %n", &delta);
            pos += delta;
            if (count == EOF) break;
        }
        PR_SetLogBuffering(isSync ? 0 : bufSize);

#ifdef XP_UNIX
        if ((getuid() != geteuid()) || (getgid() != getegid())) {
            return;
        }
#endif /* XP_UNIX */

        ev = PR_GetEnv("NSPR_LOG_FILE");
        if (ev && ev[0]) {
            if (!PR_SetLogFile(ev)) {
#ifdef XP_PC
                char* str = PR_smprintf("Unable to create nspr log file '%s'\n", ev);
                if (str) {
                    OutputDebugStringA(str);
                    PR_smprintf_free(str);
                }
#else
                fprintf(stderr, "Unable to create nspr log file '%s'\n", ev);
#endif
            }
        } else {
#ifdef _PR_USE_STDIO_FOR_LOGGING
            logFile = stderr;
#else
            logFile = _pr_stderr;
#endif
        }
    }
}