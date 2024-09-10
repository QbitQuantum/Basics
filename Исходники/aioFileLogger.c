void aiovFileLogger(int priority, const char *format, va_list optional_arguments) {
    int n = 0;
    int error = EXIT_SUCCESS;
    int internalError = EXIT_SUCCESS;
    const int LogMask = setlogmask(0);

    /* Check priority against setlogmask values. */
    if ((LOG_MASK(LOG_PRI(priority)) & LogMask) != 0) {
        va_list optional_arguments;
        char logMsg[2048];
        char logFormat[1024];
        char *cursor = logFormat;
        struct tm now_tm;
        time_t now;

        (void) time(&now);
        cursor += strftime(cursor, sizeof (logFormat), "%h %e %T ", localtime_r(&now, &now_tm));

        if (LogTag) {
            cursor += sprintf(cursor, "%s: ", LogTag);
        }

        if (LogStat & LOG_PID) {
            if (LogStat & LOG_TID) {
                const pid_t tid = gettid();
                n = sprintf(cursor, "[%d:%d]", (int) getpid(), (int) tid);
            } else {
                n = sprintf(cursor, "[%d]", (int) getpid());
            }
            cursor += n;
        }

        if (LogStat & LOG_RDTSC) {
            const unsigned long long int t = rdtsc();
            cursor += sprintf(cursor, "(%llu)", t);
        } /* (LogStat & LOG_CLOCK) */

        if (LogStat & LOG_LEVEL) {
            switch (LOG_PRI(priority)) {
                case LOG_EMERG:
                    n = sprintf(cursor, "* Emergency * %s", format);
                    break;
                case LOG_ALERT:
                    n = sprintf(cursor, "* Alert * %s", format);
                    break;
                case LOG_CRIT:
                    n = sprintf(cursor, "* Critical * %s", format);
                    break;
                case LOG_ERR:
                    n = sprintf(cursor, "* Error * %s", format);
                    break;
                case LOG_WARNING:
                    n = sprintf(cursor, "* Warning * %s", format);
                    break;
                case LOG_NOTICE:
                    n = sprintf(cursor, "* Notice * %s", format);
                    break;
                case LOG_INFO:
                    n = sprintf(cursor, "* Info * %s", format);
                    break;
                case LOG_DEBUG:
                    n = sprintf(cursor, "* Debug * %s", format);
                    break;
                default:
                    n = sprintf(cursor, "* <%d> * %s", priority, format);
            } /* switch(priority) */
        } /* (LogStat & LOG_LEVEL) */

        n = vsprintf(logMsg, logFormat, optional_arguments);
#if 0
        error = pthread_mutex_lock(&fileLock);
        if (likely(EXIT_SUCCESS == error)) {

            if (unlikely(-1 == logFile)) {
                error = createFile();
                /* error already logged */
            }

            if (likely(EXIT_SUCCESS == error)) {
                ssize_t written = write(logFile, logMsg, n);
                if (written > 0) {
                    if (unlikely(written != n)) {
                        ERROR_MSG("only %d byte(s) of %d has been written to %s", written, n, fullFileName);
                    }
                    fileSize += written;

                    if ((LOG_FILE_ROTATE & LogStat) || (LOG_FILE_HISTO & LogStat)) {
                        if (fileSize >= MaxSize) {
                            close(logFile);
                            logFile = -1;
                        }
                    }
                } else if (0 == written) {
                    WARNING_MSG("nothing has been written in %s", fullFileName);
                } else {
                    error = errno;
                    ERROR_MSG("write to %s error %d (%m)", fullFileName, error);
                }
            }

            internalError = pthread_mutex_unlock(&fileLock);
            if (internalError != EXIT_SUCCESS) {
                ERROR_MSG("pthread_mutex_lock fileLock error %d (%s)", internalError, strerror(internalError));
                if (EXIT_SUCCESS == error) {
                    error = internalError;
                }
            }
#endif
        } else {
            ERROR_MSG("pthread_mutex_lock fileLock error %d (%s)", error, strerror(error));
        }
    }

    /*return n;*/
}