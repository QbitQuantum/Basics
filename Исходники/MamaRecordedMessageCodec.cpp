uint32_t MamaRecordedMessageCodec::encodeChar(char*& buffer, MamaMsgField& mmf)
{
	char mfv = mmf.getChar();
	size_t s = sizeof(mfv);
	memcpy(buffer, &mfv, s);
	buffer += s;
	//printf("Encoding Char Field [%d] = %c...\n", s, mfv);
	return s;
}