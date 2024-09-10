void LicenseParser::parseLicensesFile (Tokeniser& tokeniser, const std::string& filename)
{
	for (;;) {
		std::string token = tokeniser.getToken();
		if (token.empty())
			break;
		if (tokeniser.getLine() > 1) {
			tokeniser.ungetToken();
			break;
		}
	}
	std::size_t lastLine = 1;
	for (;;) {
		std::string token = tokeniser.getToken();
		if (token.empty())
			break;

		if (string::contains(token, "base/textures/") && lastLine != tokeniser.getLine()) {
			_licensesMap[os::stripExtension(token.substr(5))] = true;
			lastLine = tokeniser.getLine();
		}
	}
}