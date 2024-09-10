/**
 * @brief Provides a basic logging facility for Protlib that uses the typical logging levels
 * to allow different levels for logging and run-time debugging of protolib applications.  
 */
void PLOG(ProtoDebugLevel level, const char *format, ...)
{
    if (((unsigned int)level <= DebugLevel()) || (PL_ALWAYS == level)) 
    {
        va_list args;
        va_start(args, format);
        const char * header = "";
		switch(level) 
        {  // Print out the Logging Type before the message
            case PL_FATAL: header = "Proto Fatal: ";
                break;
			case PL_ERROR: header = "Proto Error: "; 
                break; 
			case PL_WARN: header = "Proto Warn: "; 
                break; 
			case PL_INFO: header = "Proto Info: "; 
                break; 
			case PL_DEBUG: header = "Proto Debug: "; 
                break; 
			case PL_TRACE: header = "Proto Trace: "; 
                break; 
			case PL_DETAIL: header = "Proto Detail: ";
                break; 
			case PL_MAX: header = "Proto Max: "; 
                break; 
			default:
				break;
		} 
        size_t headerLen = strlen(header);
		FILE* debugLog = DebugLog();
#ifdef _WIN32_WCE
        if (debug_window.IsOpen() && !debug_pipe.IsOpen() && ((stderr == debugLog) || (stdout == debugLog)))
        {
            char charBuffer[8192];
            charBuffer[8192] = '\0';
            int count = _vsnprintf(charBuffer, 8191, format, args);
#ifdef _UNICODE
            wchar_t wideBuffer[8192];
            count = mbstowcs(wideBuffer, charBuffer, count);
            count *= sizeof(wchar_t);
            const char* theBuffer = (char*)wideBuffer;
#else
            const char* theBuffer = charBuffer;
#endif // if/else _UNICODE
            debug_window.Print(theBuffer, count);
        }
        else 
#endif  // _WIN32_WCE
#ifndef SIMULATE
        if (debug_pipe.IsOpen())
#else
   	    if (false)//always fails for simulation
#endif // if/else n SIMULATE
        {
            char buffer[8192];
            buffer[8191] = '\0';
#ifdef _WIN32_WCE
            unsigned int count = (unsigned int)_vsnprintf(buffer, 8191, format, args) + 1;
#else
#ifdef WIN32
            strcpy(buffer, header);
            unsigned int count = (unsigned int)_vsnprintf(buffer + headerLen, 8191-headerLen, format, args) + 1;
            count += (unsigned int)headerLen;
#else
            strcpy(buffer, header);
            unsigned int count = (unsigned int)vsnprintf(buffer + headerLen, 8191-headerLen, format, args) + 1;
            count += headerLen;

#endif
#endif  // if/else _WIN32_WCE
            if (count > 8192) count = 8192;
#ifndef SIMULATE
            if (!debug_pipe.Send(buffer, count))
#else 
			if (true)
#endif //if/else n SIMULATE
            {
                // We have no recourse but to go to stderr here
                fprintf(stderr, "PLOG() error: unable to send to debug pipe!!!\n");
                vfprintf(stderr, format, args);
                fflush(stderr);
            }
        }
        else
        {
#ifdef __ANDROID__
            android_LogPriority prio;
            switch(level)
            {
                case PL_FATAL:
                    prio = ANDROID_LOG_FATAL;
                    break;
                case PL_ERROR:
                    prio = ANDROID_LOG_ERROR;
                    break;
                case PL_WARN:
                    prio = ANDROID_LOG_WARN;
                    break;
                case PL_INFO:
                    prio = ANDROID_LOG_INFO;
                    break;
                case PL_DEBUG:
                    prio = ANDROID_LOG_DEBUG;
                    break;
                case PL_TRACE:
                    prio = ANDROID_LOG_VERBOSE;
                case PL_DETAIL: /* explicit fallthrough */
                case PL_MAX:    /* explicit fallthrough */
                case PL_ALWAYS: /* explicit fallthrough */
                default:
                    prio = ANDROID_LOG_DEFAULT;
                    break;
            }
            __android_log_vprint(prio, "protolib", format, args);
#else
            fprintf(debugLog, "%s", header);
            vfprintf(debugLog, format, args);
            fflush(debugLog);
#endif
        }
        va_end(args);   
    }

} // End PLOG