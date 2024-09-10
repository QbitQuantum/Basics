Value get_char() {
	Value value;
	//value.character = getwchar();
	wscanf(L"%lc",&(value.character));
	value.integer = value.character & 0xFFFF;

	return value;
}