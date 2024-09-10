static tstring formatIntegerValue(uint64 value)
{
	typedef tstring::reverse_iterator rev_iter;
	typedef tstring::const_reverse_iterator c_rev_iter;

	const tstring rawResult = Core::format<uint64>(value);

	const size_t  numDigits = (rawResult[0] != TXT('-')) ? rawResult.length() : (rawResult.length()-1);
	const tstring separator = getGroupSeparator();
	const size_t  numSeps = (numDigits-1) / 3;
	const size_t  total = rawResult.length() + (numSeps * separator.length());

	tstring result = tstring(total, TXT(' '));

	c_rev_iter it = rawResult.rbegin();
	c_rev_iter end = rawResult.rend();

	size_t   digits = 0;
	size_t   seps = 0;
	rev_iter output = result.rbegin();

	while (it != end)
	{
		*output++ = *it++;

		if ( ((++digits % 3) == 0) && (seps++ != numSeps) )
			output = std::copy(separator.rbegin(), separator.rend(), output);
	}

	return result;
}