static inline char *_itoa(char *bufend, uintmax_t value)
{
		const char *digits = "0123456789";
		ITOA(bufend, value, 10, digits);
		return bufend;
}