/**
 * @brief detects is a word is Capitalized
 *
 * @param str the word to be checked
 * @return true if the word is Capitalized, false otherwise
 */
nat_boolean_t isCapital(const wchar_t* str)
{
    int i = 0;
    if (iswupper(str[i])) {
	nat_boolean_t ok = 1;
	i++;
	while(ok && str[i]) {
	    if (!iswlower(str[i])) ok = 0;
	    i++;
	}
	return ok;
    } else {
	return 0;
    }
}