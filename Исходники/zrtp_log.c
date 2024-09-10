/*----------------------------------------------------------------------------*/
static void zrtp_log(uint8_t is_clean, const char *sender, uint32_t level,  const char *format, va_list marker)
{ 	
#if (defined(ZRTP_USE_STACK_MINIM) && (ZRTP_USE_STACK_MINIM == 1))
	char *log_buffer = zrtp_sys_alloc(ZRTP_LOG_BUFFER_SIZE);
#else
	char log_buffer[ZRTP_LOG_BUFFER_SIZE];
#endif
	char* sline = log_buffer;
	uint32_t offset = 0;
	int len = 0;
	
	if (!sline) {
		return;
	}
	
	if (!is_clean) {
		/* Print sender with left aligment */	
		uint32_t sender_len = strlen(sender);
		*sline++ = ' ';
		*sline++ = '[';
		if (sender_len <= ZRTP_LOG_SENDER_MAX_LEN) {
			while (sender_len < ZRTP_LOG_SENDER_MAX_LEN) {
				*sline++ = ' ', ++sender_len;
			}
			while (*sender) {
				*sline++ = *sender++;
			}
		} else {
			int i = 0;
			for (i=0; i<ZRTP_LOG_SENDER_MAX_LEN; ++i) {
				*sline++ = *sender++;
			}
		}
		
		*sline++ = ']';
		*sline++ = ':';
		offset += 3 + ZRTP_LOG_SENDER_MAX_LEN;
			
		*sline++ = ' ';
		offset += 1; 
	}
	
	/* Print Message itself */
#if (ZRTP_PLATFORM == ZP_WIN32) || (ZRTP_PLATFORM == ZP_WIN64) || (ZRTP_PLATFORM == ZP_WINCE)
#	if (_MSC_VER >= 1400) && (ZRTP_PLATFORM != ZP_WINCE)
	len = _vsnprintf_s(sline, ZRTP_LOG_BUFFER_SIZE-offset-1, ZRTP_LOG_BUFFER_SIZE-offset-1, format, marker);
#	else
	len = _vsnprintf(sline, ZRTP_LOG_BUFFER_SIZE-offset, format, marker);
#	endif
#elif (ZRTP_PLATFORM == ZP_WIN32_KERNEL)
	RtlStringCchVPrintfA(sline, ZRTP_LOG_BUFFER_SIZE-offset, format, marker);
#elif (ZRTP_PLATFORM == ZP_LINUX) || (ZRTP_PLATFORM == ZP_DARWIN) || (ZRTP_PLATFORM == ZP_BSD) || (ZRTP_PLATFORM == ZP_ANDROID)
	len = vsnprintf(sline, ZRTP_LOG_BUFFER_SIZE-offset, format, marker);
#elif (ZRTP_PLATFORM == ZP_SYMBIAN)
	len = vsprintf(sline, format, marker);
#endif

	if ((len > 0) && log_writer) {
		(*log_writer)(level, log_buffer, len+offset, offset);
	}

#if (defined(ZRTP_USE_STACK_MINIM) && (ZRTP_USE_STACK_MINIM == 1))
	zrtp_sys_free(log_buffer);
#endif
}