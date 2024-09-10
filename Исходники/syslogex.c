static void
__vsyslogex_chk(int pri, int flag, pid_t cpid, pid_t ctid, const char *fmt, va_list ap) {
    struct tm now_tm;
    time_t now;
    int fd;
    FILE *f;
    char *buf = 0;
    size_t bufsize = 0;
    size_t prioff, msgoff;
#ifndef NO_SIGPIPE
    struct sigaction action, oldaction;
    int sigpipe;
#endif
    int saved_errno = errno;
    char failbuf[3 * sizeof (pid_t) + sizeof "out of memory []"];
    const int LogMask = setlogmask(0);

#ifdef _DEBUGFLAGS_H_
    {
        static unsigned int registered = 0;
        if (unlikely(0 == registered)) {
            registered = 1; /* dirty work around to avoid deadlock: syslogex->register->syslogex */
            registered = (registerLibraryDebugFlags(&debugFlags) == EXIT_SUCCESS);
        }
    }
#endif /*_DEBUGFLAGS_H_*/

#define INTERNALLOG LOG_ERR|LOG_CONS|LOG_PERROR|LOG_PID
    /* Check for invalid bits. */
    if (unlikely(pri & ~(LOG_PRIMASK | LOG_FACMASK))) {
        /*syslog(INTERNALLOG,
               "syslog: unknown facility/priority: %x", pri);*/
        WARNING_MSG("unknown facility/priority: %x", pri);
        pri &= LOG_PRIMASK | LOG_FACMASK;
    }

    /* Check priority against setlogmask values. */
    if (unlikely((LOG_MASK(LOG_PRI(pri)) & LogMask) == 0))
        return;

    /* Set default facility if none specified. */
    if (unlikely((pri & LOG_FACMASK) == 0))
        pri |= LogFacility;

    /* Build the message in a memory-buffer stream.  */
    f = open_memstream(&buf, &bufsize);
    if (unlikely(f == NULL)) {
        /* We cannot get a stream.  There is not much we can do but
           emitting an error messages with the Process ID.  */
        char numbuf[3 * sizeof (pid_t)];
        char *nump;
        char *endp = __stpcpy(failbuf, "out of memory [");
        pid_t pid = getpid();

        nump = numbuf + sizeof (numbuf);
        /* The PID can never be zero.  */
        do {
            *--nump = '0' + pid % 10;
        } while ((pid /= 10) != 0);

        endp = mempcpy((void*) endp, (const void*) nump, (size_t) ((numbuf + sizeof (numbuf)) - nump));
        *endp++ = ']';
        *endp = '\0';
        buf = failbuf;
        bufsize = endp - failbuf;
        msgoff = 0;
    } else {
        __fsetlocking(f, FSETLOCKING_BYCALLER);
        prioff = fprintf(f, "<%d>", pri);
        (void) time(&now);
        f->_IO_write_ptr += strftime(f->_IO_write_ptr,
                f->_IO_write_end - f->_IO_write_ptr,
                "%h %e %T ",
                localtime_r(&now, &now_tm));
        /*f->_IO_write_ptr += strftime_l (f->_IO_write_ptr,
                                          f->_IO_write_end - f->_IO_write_ptr,
                                          "%h %e %T ",
                                          localtime_r (&now, &now_tm));*/
        msgoff = ftell(f);
        if (LogTag == NULL)
            LogTag = __progname;
        if (LogTag != NULL)
            fputs_unlocked(LogTag, f);
        if (LogStat & LOG_PID) {
            const pid_t pid = ((0 == cpid) ? getpid() : cpid);
            if (LogStat & LOG_TID) {
                const pid_t tid = ((0 == ctid) ? gettid() : ctid);
                fprintf(f, "[%d:%d]", (int) pid, (int) tid);
            } else {
                fprintf(f, "[%d]", (int) pid);
            }
        }

        if (LogStat & LOG_RDTSC) {
            const unsigned long long int t = rdtsc();
            fprintf(f, "(%llu)", t);
        } /* (LogStat & LOG_RDTSC) */

        if (LogStat & LOG_CLOCK) {
            #if HAVE_CLOCK_GETTIME
                struct timespec timeStamp;
                if (clock_gettime(CLOCK_MONOTONIC,&timeStamp) == 0) {
                    fprintf(f,"(%lu.%.9d)",timeStamp.tv_sec,timeStamp.tv_nsec);
                } else {
                    const int error = errno;
                    ERROR_MSG("clock_gettime CLOCK_MONOTONIC error %d (%m)",error);
            }
            #else
                static unsigned int alreadyPrinted = 0;
                if (unlikely(0 == alreadyPrinted)) {
                    ERROR_MSG("clock_gettime  not available on this system");
                    alreadyPrinted = 1;
                }
            #endif
        }  /* (LogStat & LOG_CLOCK) */

        if (LogStat & LOG_LEVEL) {
            switch (LOG_PRI(pri)) {
                case LOG_EMERG:
                    fprintf(f, "[EMERG]");
                    break;
                case LOG_ALERT:
                    fprintf(f, "[ALERT]");
                    break;
                case LOG_CRIT:
                    fprintf(f, "[CRIT]");
                    break;
                case LOG_ERR:
                    fprintf(f, "[ERROR]");
                    break;
                case LOG_WARNING:
                    fprintf(f, "[WARNING]");
                    break;
                case LOG_NOTICE:
                    fprintf(f, "[NOTICE]");
                    break;
                case LOG_INFO:
                    fprintf(f, "[INFO]");
                    break;
                case LOG_DEBUG:
                    fprintf(f, "[DEBUG]");
                    break;
            } /* switch(LOG_PRI(pri))*/
        } /* (LogStat & LOG_LEVEL) */

        if (LogTag != NULL) {
            putc_unlocked(':', f);
            putc_unlocked(' ', f);
        }

        /* Restore errno for %m format.  */
        __set_errno(saved_errno);

        /* We have the header.  Print the user's format into the
         buffer.  */
        if (flag == -1) {
            vfprintf(f, fmt, ap);
        } else {
            __vfprintf_chk(f, flag, fmt, ap);
        }

        /* Close the memory stream; this will finalize the data
           into a malloc'd buffer in BUF.  */
        fclose(f);
    }

    /* Output to stderr if requested. */
    if (LogStat & LOG_PERROR) {
        struct iovec iov[2];
        register struct iovec *v = iov;

        v->iov_base = buf + msgoff;
        v->iov_len = bufsize - msgoff;
        /* Append a newline if necessary.  */
        if (buf[bufsize - 1] != '\n') {
            ++v;
            v->iov_base = (char *) "\n";
            v->iov_len = 1;
        }

        pthread_cleanup_push(free, buf == failbuf ? NULL : buf);

        /* writev is a cancellation point.  */
        (void) writev(STDERR_FILENO, iov, v - iov + 1);

        pthread_cleanup_pop(0);
    }

    /* Prepare for multiple users.  We have to take care: open and
  write are cancellation points.  */
    struct cleanup_arg clarg;
    clarg.buf = buf;
    clarg.oldaction = NULL;
    pthread_cleanup_push(cancel_handler, &clarg);
    pthread_mutex_lock(&syslogex_lock);

#ifndef NO_SIGPIPE
    /* Prepare for a broken connection.  */
    memset(&action, 0, sizeof (action));
    action.sa_handler = sigpipe_handler;
    sigemptyset(&action.sa_mask);
    sigpipe = __sigaction(SIGPIPE, &action, &oldaction);
    if (sigpipe == 0)
        clarg.oldaction = &oldaction;
#endif

    /* Get connected, output the message to the local logger. */
    if (!connected) {
        openlog_internal(LogTag, LogStat | LOG_NDELAY, 0);
    }

    /* If we have a SOCK_STREAM connection, also send ASCII NUL as
  a record terminator.  */
    if (LogType == SOCK_STREAM) {
        ++bufsize;
    }

    if (!connected || __send(LogFile, buf, bufsize, send_flags) < 0) {
        if (connected) {
            /* Try to reopen the syslog connection.  Maybe it went
          down.  */
            closelog_internal();
            openlog_internal(LogTag, LogStat | LOG_NDELAY, 0);
        }

        if (!connected || __send(LogFile, buf, bufsize, send_flags) < 0) {
            closelog_internal(); /* attempt re-open next time */
            /*
             * Output the message to the console; don't worry
             * about blocking, if console blocks everything will.
             * Make sure the error reported is the one from the
             * syslogd failure.
             */
            if (LogStat & LOG_CONS &&
                    (fd = __open(_PATH_CONSOLE, O_WRONLY | O_NOCTTY, 0)) >= 0) {
                dprintf(fd, "%s\r\n", buf + msgoff);
                (void) __close(fd);
            }
        }
    }

#ifndef NO_SIGPIPE
    if (sigpipe == 0)
        __sigaction(SIGPIPE, &oldaction, (struct sigaction *) NULL);
#endif

    /* End of critical section.  */
    pthread_cleanup_pop(0);
    pthread_mutex_unlock(&syslogex_lock);

    if (buf != failbuf) {
        free(buf);
    }
}