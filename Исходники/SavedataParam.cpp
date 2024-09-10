inline static std::string FixedToString(const char *str, size_t n)
{
	return std::string(str, strnlen(str, n));
}