void svOutput::Printf(
    svLogLevel level, const char *format, va_list ap)
{
    if (!debug && level == svLOG_DEBUG) return;

    pthread_mutex_lock(&mutex);
#ifndef __WIN32__

    if (log_file != NULL) {
        switch (level) {
        case svLOG_DEBUG:
            fprintf(log_file, "DEBUG: ");
            break;
        case svLOG_ERR:
            fprintf(log_file, "ERROR: ");
            break;
        default:
            break;
        }
        vfprintf(log_file, format, ap);
        fputc('\n', log_file);
    }
#ifdef __ANDROID__
    int priority;
    switch (level) {
    case svLOG_DEBUG:
        priority = ANDROID_LOG_DEBUG;
        break;
    case svLOG_INFO:
        priority = ANDROID_LOG_INFO;
        break;
    case svLOG_ERR:
        priority = ANDROID_LOG_ERROR;
        break;
    }
    __android_log_vprint(priority, "Suva", format, ap);
#elif defined(HAVE_SYSLOG_H)
    if (log_facility == 0) {
        switch (level) {
        case svLOG_DEBUG:
            fprintf(stderr, "DEBUG: ");
            break;
        case svLOG_ERR:
            fprintf(stderr, "ERROR: ");
            break;
        default:
            break;
        }
        vfprintf(stderr, format, ap);
        fputc('\n', stderr);
        pthread_mutex_unlock(&mutex);
        return;
    }

    int priority = log_facility;
    switch (level) {
    case svLOG_DEBUG:
        priority |= LOG_DEBUG;
        break;
    case svLOG_INFO:
        priority |= LOG_INFO;
        break;
    case svLOG_ERR:
        priority |= LOG_ERR;
        break;
    }
    vsyslog(priority, format, ap);
#endif // __ANDROID__
#else
#define MSG_EVENT       0x00000064L
    if (el_source) {
        char message[512];
        vsnprintf(message, sizeof(message), format, ap);
        char *log_str[1];
        log_str[0] = message;
        DWORD el_type = EVENTLOG_INFORMATION_TYPE;
        switch (level) {
        case svLOG_DEBUG:
            el_type = EVENTLOG_WARNING_TYPE;
        case svLOG_ERR:
            el_type = EVENTLOG_ERROR_TYPE;
        }
        ReportEvent(el_source, el_type, 0,
            MSG_EVENT,
            NULL, 1, 0, (const char **)log_str, NULL);
    }
    else {
        switch (level) {
        case svLOG_DEBUG:
            fprintf(stdout, "DEBUG: ");
            break;
        case svLOG_ERR:
            fprintf(stdout, "ERROR: ");
            break;
        default:
            break;
        }
        vfprintf(stdout, format, ap);
        fputc('\n', stdout);
    }
#endif
    pthread_mutex_unlock(&mutex);
}