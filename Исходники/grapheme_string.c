/* {{{ grapheme_extract_count_iter - grapheme iterator for grapheme_extract COUNT */
static inline int32_t
grapheme_extract_count_iter(UBreakIterator *bi, int32_t size, unsigned char *pstr, int32_t str_len)
{
	int pos = 0, next_pos = 0;
	int ret_pos = 0;

	while ( size ) {
		next_pos = ubrk_next(bi);

		if ( UBRK_DONE == next_pos ) {
			break;
		}
		pos = next_pos;
		size--;
	}

	/* pos is one past the last UChar - and represent the number of code units to
		advance in the utf-8 buffer
	*/

	U8_FWD_N(pstr, ret_pos, str_len, pos);

	return ret_pos;
}