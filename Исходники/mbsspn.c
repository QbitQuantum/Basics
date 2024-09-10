/*
 * @implemented
 */
size_t _mbsspn (const unsigned char *str1, const unsigned char *str2)
{
    int c;
    const unsigned char *save = str1;

    while ((c = _mbsnextc (str1))) {

	if (_mbschr (str2, c) == 0)
	    break;

	str1 = _mbsinc ((unsigned char *) str1);

    }

    return str1 - save;
}