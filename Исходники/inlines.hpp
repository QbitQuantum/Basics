inline UString readUTF8String(S& input) {
	uint16_t len = 0;
	readRaw(input, len);

	UString rv(len, 0);
	std::vector<char> buffer(len);
	input.read(&buffer[0], len);

	int32_t olen = 0;
	UErrorCode status = U_ZERO_ERROR;
	u_strFromUTF8(&rv[0], len, &olen, &buffer[0], len, &status);

	rv.resize(olen);

	return rv;
}