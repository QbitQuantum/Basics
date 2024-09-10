int get4(QFile& file) {
	char ch;
	file.getChar(&ch);
	int res = ch & 0xff;
	file.getChar(&ch);
	res |= (ch << 8);
	file.getChar(&ch);
	res |= (ch << 16);
	file.getChar(&ch);
	res |= (ch << 24);
	return res;
}