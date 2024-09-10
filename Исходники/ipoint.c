gchar *
sary_ipoint_locale (SaryText *text)
{
    gchar *cursor, *eof;
    SaryInt maxlen, len;

    if (sary_text_is_eof(text)) {
	return NULL;
    }

    eof    = sary_text_get_eof(text);
    cursor = sary_text_get_cursor(text);
    maxlen = eof - cursor;

    len    = mblen(cursor, maxlen);
    if (len == -1) {
	/* invalid character */
	gchar *bof = sary_text_get_bof(text);
	g_warning("invalid character at %d", cursor - bof);
	len = 1;
    }

    sary_text_forward_cursor(text, len);
    return cursor;
}