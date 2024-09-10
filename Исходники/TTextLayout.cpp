static inline int Tmblen(const char* s, size_t n)
{
	int result = mblen(s, n);
	if (result > 0)
		return result;
	else
		return 1;
}