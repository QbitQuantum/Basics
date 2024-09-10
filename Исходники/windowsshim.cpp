int vasprintf(char **strp, const char *fmt, va_list ap)
{
   auto r = -1, size = _vscprintf(fmt, ap);

	if ((size >= 0) && (size < INT_MAX))
	{
		*strp = static_cast<char *>(malloc(size + 1)); //+1 for null
		if (*strp)
		{
			r = vsnprintf(*strp, size + 1, fmt, ap);  //+1 for null
			if ((r < 0) || (r > size))
			{
				free(*strp); 
				*strp = nullptr;
				r = -1;
			}
		}
	}
	else { *strp = nullptr; }

	return(r);
}