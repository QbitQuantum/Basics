Text TextFileReaderInternal::readAll(Text const& lineEndings) throw()
{
	Text text;
	
	while(isEof() == false)
	{
		text <<= readLine();
		
		if(isEof() == false && lineEndings.length() > 0)
			text <<= lineEndings;
	}
	
	return text;
}