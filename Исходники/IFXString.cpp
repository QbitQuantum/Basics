// Somewhat brute force, but works.  Rewrite if necessary for speed.
IFXString& IFXString::VSPrintf(const IFXCHAR* fmt, va_list ap)
{
	int sz = m_BufferLength;

	if(!m_BufferLength)
	{ // start at 80 bytes, seems reasonable (1 tty line)
		NewBuffer(80);
		sz = m_BufferLength;
	}
	else
	{
		NewBuffer(sz);
	}

	while(IFX_TRUE)
	{
		int n =  vswprintf((IFXCHAR*)m_Buffer, m_BufferLength, fmt, ap);

		if(n > -1 && n < sz)
		{
			break;
		}
		if(n > -1)
		{
			sz = n+1;
		}
		else
		{
			sz *= 2;
		}
		NewBuffer(sz);
	}

	return *this;
}