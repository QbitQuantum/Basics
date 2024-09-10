_nc_wcrtomb(char *target, wchar_t source, mbstate_t * state)
{
    int result;

    if (target == 0) {
	wchar_t temp[2];
	const wchar_t *tempp = temp;
	temp[0] = source;
	temp[1] = 0;
	result = (int) wcsrtombs(NULL, &tempp, 0, state);
    } else {
	result = (int) wcrtomb(target, source, state);
    }
    if (!isEILSEQ(result) && (result == 0))
	result = 1;
    return (size_t) result;
}