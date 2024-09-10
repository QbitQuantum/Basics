u_long xatoi(const char *cp)
{
	u_long val;
	char base;
	char c;

	/*
	 * 0x=hex
	 * 0=octal
	 * isdigit=decimal
	 */
	c = *cp;
	if (!isdigit(c))
		return 0;
	val = 0;
	base = 10;
	if (c == '0') {
		c = *++cp;
		if (c == 'x' || c == 'X') {
			base = 16;
			c = *++cp;
		} else
			base = 8;
	}
	for (;;) {
#if 0
		if (isascii(c) && isdigit(c)) {
#else
		if (isdigit(c)) {
#endif
			val = (val * base) + (c - '0');
			c = *++cp;
#if 0
		} else if (base == 16 && isascii(c) && isxdigit(c)) {
#else
		} else if (base == 16 && isxdigit(c)) {
#endif
			val = (val << 4) | (c + 10 - (islower(c) ? 'a' : 'A'));
			c = *++cp;
		} else
			break;
	}
	return val;
}

void MemDump(void *mem, u_long len, u_char wordAccess)
{
	u_long memaddr = (u_long)mem;
	u_long addr;
	u_long i = 0;
	u_char line[17];	/* character display buffer */
	u_char j, k, l;
	u_char even = 1;
	u_short w = 0;
	SYS_DECL_LOCK;

	if (wordAccess) {
		memaddr &= ~0x1;	/* make even */
		len <<= 1;	/* make double */
	}

	memset(line, 0, sizeof(line));
	l = 0;
	addr = memaddr & ~0x0f;
	if (len <= 0)
		return;

	SYS_LOCK(); /* not non-reentrant code but for clean display */
	do {
		if ((addr & 0x0f) == 0)
			printf("%08lx  ", addr);
		if (addr < memaddr) {
			printf("  ");
			line[l++] = ' ';
		} else {
			u_char b;
			if (wordAccess) {
				if (even) {
					w = *((u_short *)addr);
					b = (u_char)((w >> 8) & 0xff);
					even = 0;
				} else {
					b = (u_char)(w & 0xff);
					even = 1;
				}
			} else
				b = *((u_char *)addr);
			printf("%02x", (int)b);
			i++;
			//line[l++] =isspace(b) ? ' ' : (isprint(b) ? b : '.');
			line[l++] =  (b >= 0x20 && b <= 0x7e) ? b : '.';

		}