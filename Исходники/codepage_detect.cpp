/**
 * @brief Remove prefix from the text.
 * @param [in] text Text to process.
 * @param [in] prefix Prefix to remove.
 * @return Text without the prefix.
 */
static const char *EatPrefix(const char *text, const char *prefix)
{
	int len = strlen(prefix);
	if (len)
		if (_memicmp(text, prefix, len) == 0)
			return text + len;
	return 0;
}