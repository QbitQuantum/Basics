static FcBool
write_chars (FILE *f, const FcChar8 *chars)
{
    FcChar8    c;
    while ((c = *chars++))
    {
	switch (c) {
	case '"':
	case '\\':
	    if (PUTC ('\\', f) == EOF)
		return FcFalse;
	    /* fall through */
	default:
	    if (PUTC (c, f) == EOF)
		return FcFalse;
	}
    }
    return FcTrue;
}