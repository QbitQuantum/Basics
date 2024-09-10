void csp_debug_ex(csp_debug_level_t level, const char * format, ...) {

	const char * color = "";
	va_list args;
	va_start(args, format);

	/* Don't print anything if log level is disabled */
	switch(level) {
	case CSP_INFO:
		if (!levels_enable[CSP_INFO])
			return;
		break;
	case CSP_ERROR:
		if (!levels_enable[CSP_ERROR])
			return;
		color = "\E[1;31m";
		break;
	case CSP_WARN:
		if (!levels_enable[CSP_WARN])
			return;
		color = "\E[0;33m";
		break;
	case CSP_BUFFER:
		if (!levels_enable[CSP_BUFFER])
			return;
		color = "\E[0;33m";
		break;
	case CSP_PACKET:
		if (!levels_enable[CSP_PACKET])
			return;
		color = "\E[0;32m";
		break;
	case CSP_PROTOCOL:
		if (!levels_enable[CSP_PROTOCOL])
			return;
		color = "\E[0;34m";
		break;
	case CSP_LOCK:
		if (!levels_enable[CSP_LOCK])
			return;
		color = "\E[0;36m";
		break;
	}

	/* If csp_debug_hook symbol is defined, pass on the message.
	 * Otherwise, just print with pretty colors ... */
	if (csp_debug_hook || csp_debug_hook_func) {
		char buf[250];
		vsnprintf(buf, 250, format, args);
		if (csp_debug_hook) {
			csp_debug_hook(level, buf);
		} else if (csp_debug_hook_func) {
			csp_debug_hook_func(level, buf);
		}
	} else {
		if (csp_debug_printf_hook)
			csp_debug_printf_hook(level);

#if defined(CSP_WINDOWS)
		vprintf(format, args);
#else
		printf("%s", color);
		vprintf(format, args);
		printf("\E[0m");
#endif
	}

	va_end(args);

}