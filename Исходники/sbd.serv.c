int
ctrlSbdDebug(struct debugReq  *pdebug)
{
    static char   fname[]="ctrlSbdDebug()";
    int           opCode;
    int           level;
    int           newClass;
    int           options;
    char          logFileName[MAXLSFNAMELEN];
    char          lsfLogDir[MAXPATHLEN];
    char          *dir;
    char          dynDbgEnv[MAXPATHLEN];

    memset(logFileName, 0, sizeof(logFileName));
    memset(lsfLogDir, 0, sizeof(lsfLogDir));

    opCode = pdebug->opCode;
    level = pdebug->level;
    newClass = pdebug->logClass;
    options = pdebug->options;

    if (pdebug->logFileName[0] != '\0') {
        if (((dir = strrchr(pdebug->logFileName,'/')) != NULL) ||
            ((dir = strrchr(pdebug->logFileName,'\\')) != NULL)) {
            dir++;
            ls_strcat(logFileName, sizeof(logFileName), dir);
            *(--dir) = '\0';
            ls_strcat(lsfLogDir, sizeof(lsfLogDir), pdebug->logFileName);
        }
        else {
            ls_strcat(logFileName, sizeof(logFileName), pdebug->logFileName);
            if (daemonParams[LSF_LOGDIR].paramValue
                && *(daemonParams[LSF_LOGDIR].paramValue)) {
                ls_strcat(lsfLogDir, sizeof(lsfLogDir),
                          daemonParams[LSF_LOGDIR].paramValue);
            }
            else {
                lsfLogDir[0] = '\0';
            }
        }
        ls_strcat(logFileName, sizeof(logFileName), ".sbatchd");
    }
    else {
  	ls_strcat(logFileName, sizeof(logFileName), "sbatchd");
        if (daemonParams[LSF_LOGDIR].paramValue
            && *(daemonParams[LSF_LOGDIR].paramValue)) {
            ls_strcat(lsfLogDir, sizeof(lsfLogDir),
                      daemonParams[LSF_LOGDIR].paramValue);
        } else {
            lsfLogDir[0] = '\0';
        }
    }

    if (options==1) {
        struct config_param *plp;
        for (plp = daemonParams; plp->paramName != NULL; plp++) {
            if (plp->paramValue != NULL)
                FREEUP(plp->paramValue);
        }

        if (initenv_(daemonParams, env_dir) < 0){
            ls_openlog("sbatchd", daemonParams[LSF_LOGDIR].paramValue,
                       (debug > 1), daemonParams[LSF_LOG_MASK].paramValue);
  	    ls_syslog(LOG_ERR, I18N_FUNC_FAIL_MM, fname, "initenv_");
            die(SLAVE_FATAL);
            return -1;
        }

        getLogClass_(daemonParams[LSB_DEBUG_SBD].paramValue,
                     daemonParams[LSB_TIME_SBD].paramValue);
        closelog();
        if (debug > 1)
            ls_openlog("sbatchd", daemonParams[LSF_LOGDIR].paramValue, TRUE,
                       daemonParams[LSF_LOG_MASK].paramValue);
        else
            ls_openlog("sbatchd", daemonParams[LSF_LOGDIR].paramValue, FALSE,
                       daemonParams[LSF_LOG_MASK].paramValue);

        if (logclass & LC_TRACE)
            ls_syslog(LOG_DEBUG, "%s: logclass=%x", fname, logclass);

        cleanDynDbgEnv();

        return(LSBE_NO_ERROR);
    }

    if (opCode==SBD_DEBUG) {
        putMaskLevel(level, &(daemonParams[LSF_LOG_MASK].paramValue));

        if (newClass>=0) {
            logclass = newClass;

            sprintf(dynDbgEnv, "%d", logclass);
            putEnv("DYN_DBG_LOGCLASS", dynDbgEnv);
        }

        if ( pdebug->level>=0 ){
            closelog();
            if (debug > 1)
                ls_openlog(logFileName, lsfLogDir, TRUE,
                           daemonParams[LSF_LOG_MASK].paramValue);
            else
                ls_openlog(logFileName, lsfLogDir, FALSE,
                           daemonParams[LSF_LOG_MASK].paramValue);

            putEnv("DYN_DBG_LOGDIR", lsfLogDir);
            putEnv("DYN_DBG_LOGFILENAME", logFileName);
            sprintf(dynDbgEnv, "%d", pdebug->level);
            putEnv("DYN_DBG_LOGLEVEL", dynDbgEnv);
        }
    }
    else if (opCode == SBD_TIMING) {
        if (level>=0)
 	    timinglevel = level;
        if (pdebug->logFileName[0] != '\0') {
            if (debug > 1)
                ls_openlog(logFileName, lsfLogDir,
                           TRUE, daemonParams[LSF_LOG_MASK].paramValue);
            else
                ls_openlog(logFileName, lsfLogDir,
                           FALSE, daemonParams[LSF_LOG_MASK].paramValue);
        }
    }
    else {
        ls_perror("No this debug command!\n");
        return -1;
    }
    return (LSBE_NO_ERROR);
}