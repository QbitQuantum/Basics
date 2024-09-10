static void simpleLog_logv(int level, const char* fmt, va_list argp) {

	if (level > logLevel) {
		return;
	}

	static char outBuffer[SIMPLELOG_OUTPUTBUFFER_SIZE];

	VSNPRINTF(outBuffer, SIMPLELOG_OUTPUTBUFFER_SIZE, fmt, argp);
	simpleLog_out(level, outBuffer);
}