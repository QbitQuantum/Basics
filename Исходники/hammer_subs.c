void
hkprintf(const char *ctl, ...)
{
	__va_list va;

	if (hammer_debug_debug) {
		__va_start(va, ctl);
		kvprintf(ctl, va);
		__va_end(va);
	}
}