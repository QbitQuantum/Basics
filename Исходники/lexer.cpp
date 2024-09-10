lexer::~lexer() {
	if (state != eof) {
		scan('\0');
	}
}