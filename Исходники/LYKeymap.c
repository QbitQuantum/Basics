char *LYKeycodeToString(int c,
			int upper8)
{
    static char buf[30];
    unsigned n;
    BOOLEAN named = FALSE;

    for (n = 0; n < TABLESIZE(named_keys); n++) {
	if (named_keys[n].key == c) {
	    named = TRUE;
	    LYStrNCpy(buf, named_keys[n].name, sizeof(buf) - 1);
	    break;
	}
    }

    if (!named) {
	if (c <= 0377
	    && TOASCII(c) > TOASCII(' ')
	    && TOASCII(c) < 0177)
	    sprintf(buf, "%c", c);
	else if (upper8
		 && TOASCII(c) > TOASCII(' ')
		 && c <= 0377
		 && c <= LYlowest_eightbit[current_char_set])
	    sprintf(buf, "%c", c);
	else if (TOASCII(c) < TOASCII(' '))
	    sprintf(buf, "^%c", FROMASCII(TOASCII(c) | 0100));
	else if (c >= 0400)
	    sprintf(buf, "key-0x%x", c);
	else
	    sprintf(buf, "0x%x", c);
    }
    return buf;
}