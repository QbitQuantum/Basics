gchar *
tracker_encoding_guess_icu (const gchar *buffer,
			    gsize        size)
{
	UCharsetDetector *detector = NULL;
	const UCharsetMatch *match;
	gchar *charset = NULL;
	UErrorCode status;

	detector = ucsdet_open (&status);

	if (U_FAILURE (status))
		goto failure;

	if (size >= G_MAXINT32)
		goto failure;

	ucsdet_setText (detector, buffer, (int32_t) size, &status);

	if (U_FAILURE (status))
		goto failure;

	match = ucsdet_detect (detector, &status);

	if (U_FAILURE (status))
		goto failure;

	charset = g_strdup (ucsdet_getName (match, &status));

	if (U_FAILURE (status)) {
		g_free (charset);
		charset = NULL;
	}

	if (charset)
		g_debug ("Guessing charset as '%s'", charset);

failure:
	if (detector)
		ucsdet_close (detector);

	return charset;
}