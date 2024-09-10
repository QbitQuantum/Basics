void safe_file_scanf(const char *file, const int lineno,
		     void (*cleanup_fn) (void),
		     const char *path, const char *fmt, ...)
{
	va_list va;
	FILE *f;
	int exp_convs, ret;

	f = fopen(path, "r");

	if (f == NULL) {
		tst_brkm(TBROK | TERRNO, cleanup_fn,
			 "Failed to open FILE '%s' for reading at %s:%d",
			 path, file, lineno);
	}

	exp_convs = count_scanf_conversions(fmt);

	va_start(va, fmt);
	ret = vfscanf(f, fmt, va);
	va_end(va);

	if (ret == EOF) {
		tst_brkm(TBROK, cleanup_fn,
			 "The FILE '%s' ended prematurely at %s:%d",
			 path, file, lineno);
	}

	if (ret != exp_convs) {
		tst_brkm(TBROK, cleanup_fn,
			 "Expected %i conversions got %i FILE '%s' at %s:%d",
			 exp_convs, ret, path, file, lineno);
	}

}