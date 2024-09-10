static void TranslateToDos(doscp_t *toDos, const char *in, char *out, int count,
			   char *end, Case_t *Case, int *mangled)
{
	wchar_t buffer[12];
	wchar_t *s=buffer;
	wchar_t *t=buffer;

	/* first convert to wchar, so we get to use towupper etc. */
	native_to_wchar(in, buffer, count, end, mangled);
	buffer[count]='\0';

	*Case = NONE;
	for( ;  *s ; s++) {
		/* skip spaces & dots */
		if(*s == ' ' || *s == '.') {
			*mangled |= 3;
			continue;
		}

		if (iswcntrl(*s)) {
			/* "control" characters */
			*mangled |= 3;
			*t = '_';
		} else if (iswlower(*s)) {
			*t = towupper(*s);
			if(*Case == UPPER && !mtools_no_vfat)
				*mangled |= 1;
			else
				*Case = LOWER;
		} else if (iswupper(*s)) {
			*t = *s;
			if(*Case == LOWER && !mtools_no_vfat)
				*mangled |= 1;
			else
				*Case = UPPER;
		} else
			*t = *s;
		t++;
	}
	wchar_to_dos(toDos, buffer, out, t - buffer, mangled);
}