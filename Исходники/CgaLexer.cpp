CgaToken CgaLexer::GetToken()
{
	// Eat white space
	while (IsWhiteSpace(c)) {
		MoveNext();
	}

	// Handle identifiers
	if (IsAlpha(c)) {
		CGAString identifier;
		identifier += c;
		MoveNext();

		while (IsAlphaNumeric(c) || c == '.') {
			identifier += c;
			MoveNext();
		}

		if (identifier == "true") {
			return CreateToken(CgaTokenType::True, "true");
		}
		else if (identifier == "false") {
			return CreateToken(CgaTokenType::False, "false");
		}
		else if (identifier == "var") {
			return CreateToken(CgaTokenType::Var, "var");
		}
		else {
			return CreateToken(CgaTokenType::Identifier, identifier);
		}
	}

	// Handle Numbers
	if (IsDigit(c) || c == '.') {
		CGAString snum;
		while (IsDigit(c)) {
			snum += c;
			MoveNext();
		}
		if (c == '.') {
			snum += c;
			MoveNext();

			while (IsDigit(c)) {
				snum += c;
				MoveNext();
			}
		}
		float num = static_cast<float>(atof(snum.c_str()));
		if (c == 'r') {
			snum += c;
			MoveNext();		// Eat 'r'

			return CreateToken(CgaTokenType::ArgNumber, snum, num);
		}
		else {
			return CreateToken(CgaTokenType::Number, snum);
		}
	}

	// Handle string
	if (c == '\"') {
		MoveNext();	// Eat "
		CGAString value;
		while (c != '\"') {
			value += c;
			MoveNext();
			if (stream.eof()) break;
		}
		MoveNext();	// Eat "

		return CreateToken(CgaTokenType::String, value);
	}

	// Handle Comments
	if (c == '#') {
		// Eat till end of line
		while (c != '\n' && !stream.eof())
		{
			MoveNext();
		}

		MoveNext();	// Eat \n
	}

	// Handle additive operators
	if (c == '+' || c == '-') {
		char lastChar = c;
		CGAString op;
		op += c;
		MoveNext();

		// Handle arrow op '->'
		if (lastChar == '-' && c == '>') {
			op += c;
			MoveNext();
			return CreateToken(CgaTokenType::Arrow, op);
		}

		return CreateToken(CgaTokenType::BinaryOp, op);
	}

	// Handle multiplicative operators
	if (c == '*' || c == '/') {
		CGAString op;
		op += c;
		MoveNext();

		return CreateToken(CgaTokenType::BinaryOp, op);
	}

	// Handle conditional operators
	if (c == '<' || c == '>' || c == '!' || c == '=') {
		char lastChar = c;
		CGAString op;
		op += c;
		MoveNext();

		if (c != '=') {
			// Is not an '=='.  Emit an assign token ('=')
			return CreateToken(CgaTokenType::Assign, op);
		}

		if (
			(lastChar == '<' && c == '=') ||
			(lastChar == '>' && c == '=') ||
			(lastChar == '!' && c == '=') ||
			(lastChar == '=' && c == '=')
		) {
			op += c;
			MoveNext();
		}
		return CreateToken(CgaTokenType::BinaryOp, op);
	}

	// Handle End of file
	if (stream.eof()) {
		return CreateToken(CgaTokenType::Eof, 0);
	}

	CgaTokenType Type = CgaTokenType::Unknown;

	if (c == ';') Type = CgaTokenType::Semicolon;
	if (c == ',') Type = CgaTokenType::Comma;
	if (c == '(') Type = CgaTokenType::ParenOpen;
	if (c == ')') Type = CgaTokenType::ParenClose;
	if (c == '{') Type = CgaTokenType::CurlOpen;
	if (c == '}') Type = CgaTokenType::CurlClose;
	if (c == '|') Type = CgaTokenType::Pipe;
	if (c == ':') Type = CgaTokenType::Colon;
	if (c == '~') Type = CgaTokenType::Epsillon;

	CGAString value(1, c);
	MoveNext();
	return CreateToken(Type, value);
}