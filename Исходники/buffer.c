/* make room for at least n chars */
static int grow(buffer_t * b, size_t n)
{
	size_t used = inuse(b);
	size_t newlen = sizeof(b->initial); /* current buf is always at least as big as b->initial */

	/* simple solution to find next power of 2 */
	while (newlen < used+n) newlen <<= 1;

	/* too big? */
	if (0 < b->max && b->max < newlen) {
		if (used+n <= b->max) {
			/* This handles the case where b->max is not a power of 2. */
			newlen = b->max;
		} else {
			errno = ENOBUFS;
			checkerror(b, 0, 0);
		}
	}

	if (b->buf == b->ubuf.buf || b->buf == b->initial) {
		char *new = malloc(newlen);
		checkerror(b, NULL, new);
		memcpy(new, b->buf, used);
		b->buf = new;
	} else {