NMEBoolean NMEAutoconvertURL(NMEConstText src, NMEInt srcLen,
		NMEInt *i,
		NMEContext *context,
		void *userData)
{
	NMEInt i1, j, k, p;
	static char const * const prefix[] =
	{
		"http://", "https://", "ftp://", "mailto:", NULL
	};
	static char const punctuation[] = ",.?!:;'";
	
	// no match if first character is not a blank
	if (*i == 0)
		i1 = isBlank(src[*i]) ? *i + 1 : *i;
	else if (!isBlank(src[*i]))
		return FALSE;
	else
		i1 = *i + 1;
	
	// find prefix
	for (j = 0; prefix[j]; j++)
	{
		for (k = 0; prefix[j][k] && i1 + k < srcLen && src[i1 + k] == prefix[j][k]; k++)
			;
		if (prefix[j][k])
			continue;	// end of prefix not reached
		
		// continue until next blank/control or double-quote
		for (p = k; i1 + p < srcLen && src[i1 + p] != '"'
				&& !(src[i1 + p] >= '\0' && src[i1 + p] <= ' '); p++)
			;
		
		// give up if nothing more than prefix
		if (p == k)
			continue;
		
		// remove trailing punctuation character
		for (j = 0; punctuation[j]; j++)
			if (src[i1 + p - 1] == punctuation[j])
			{
				p--;
				break;
			}
		
		// copy link, including blank src[*i] if any
		NMEAddString(&src[*i], i1 - *i, '\0', context);	// blank
		NMEAddString("[[", -1, '\0', context);
		NMEAddString(&src[i1], p, '\0', context);
		NMEAddString("]]", -1, '\0', context);
		*i = i1 + p;
		return TRUE;
	}
	
	return FALSE;
}