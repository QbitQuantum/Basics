void
str_ucnv_update_flags(rb_str_t *self)
{
    USE_CONVERTER(cnv, self->encoding);

    bool ascii_only = true;
    bool valid_encoding = true;

    const char *pos = self->bytes;
    const char *end = pos + self->length_in_bytes;
    for (;;) {
	// iterate through the string one Unicode code point at a time
	UErrorCode err = U_ZERO_ERROR;
	UChar32 c = ucnv_getNextUChar(cnv, &pos, end, &err);
	if (U_FAILURE(err)) {
	    if (err == U_INDEX_OUTOFBOUNDS_ERROR) {
		// end of the string
		break;
	    }
	    else {
		// conversion error
		valid_encoding = false;
		ascii_only = false;
		break;
	    }
	}
	else {
	    if (c > 127) {
		ascii_only = false;
	    }
	}
    }

    ucnv_close(cnv);

    str_set_valid_encoding(self, valid_encoding);
    str_set_ascii_only(self, ascii_only);
}