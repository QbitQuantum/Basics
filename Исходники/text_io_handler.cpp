String TextIOHandler::getLine() {
	String result;
	Char buffer[2048];
	while (!feof(stdin)) {
		if (!IF_UNICODE(fgetws,fgets)(buffer, 2048, stdin)) {
			return result; // error
		}
		result += buffer;
		if (result.GetChar(result.size()-1) == _('\n')) {
			// drop newline, done
			result.resize(result.size() - 1);
			return result;
		}
	}
	return result;
}