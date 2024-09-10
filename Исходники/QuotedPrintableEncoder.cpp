int QuotedPrintableEncoderBuf::writeToDevice(char c)
{
	if (_pending != -1)
	{
		if (_pending == '\r' && c == '\n')
			writeRaw((char) _pending);
		else if (c == '\r' || c == '\n')
			writeEncoded((char) _pending);
		else
			writeRaw((char) _pending);
		_pending = -1;
	}
	if (c == '\t' || c == ' ')
	{
		_pending = charToInt(c);
		return _pending;
	}
	else if (c == '\r' || c == '\n' || c > 32 && c < 127 && c != '=')
	{
		writeRaw(c);
	}
	else
	{
		writeEncoded(c);
	}
	return charToInt(c);
}