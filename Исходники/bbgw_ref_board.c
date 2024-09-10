/* MAC address string <-> byte array from glibc. */
static uint8_t *ether_aton(char *addr_string, uint8_t * addr_bytes)
{
	size_t cnt;

	for (cnt = 0; cnt < 6; ++cnt) {
		unsigned int number;
		char ch;

		ch = _tolower(*addr_string++);
		if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
			return NULL;
		number = isdigit(ch) ? (ch - '0') : (ch - 'a' + 10);

		ch = _tolower(*addr_string);
		if ((cnt < 5 && ch != ':')
		    || (cnt == 5 && ch != '\0' && !isspace(ch))) {
			++addr_string;
			if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f'))
				return NULL;
			number <<= 4;
			number += isdigit(ch) ? (ch - '0') : (ch - 'a' + 10);

			ch = *addr_string;
			if (cnt < 5 && ch != ':')
				return NULL;
		}

		/* Store result.  */
		addr_bytes[cnt] = (unsigned char)number;

		/* Skip ':'.  */
		++addr_string;
	}

	return addr_bytes;
}