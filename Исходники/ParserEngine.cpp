void ParserEngine::parse(const char* pBuffer, std::size_t size)
{
	init();
	resetContext();
	InputSource src;
	pushContext(_parser, &src);
	if (_pContentHandler) _pContentHandler->setDocumentLocator(this);
	if (_pContentHandler) _pContentHandler->startDocument();
	std::size_t processed = 0;
	while (processed < size)
	{
		const int bufferSize = processed + PARSE_BUFFER_SIZE < size ? PARSE_BUFFER_SIZE : static_cast<int>(size - processed);
		if (!XML_Parse(_parser, pBuffer + processed, bufferSize, 0))
			handleError(XML_GetErrorCode(_parser));
		processed += bufferSize;
	}
	if (!XML_Parse(_parser, pBuffer+processed, 0, 1))
		handleError(XML_GetErrorCode(_parser));
	if (_pContentHandler) _pContentHandler->endDocument();
	popContext();
}