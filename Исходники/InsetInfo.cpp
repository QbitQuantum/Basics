void InsetInfo::read(Lexer & lex)
{
	string token;
	while (lex.isOK()) {
		lex.next();
		token = lex.getString();
		if (token == "type") {
			lex.next();
			token = lex.getString();
			type_ = nameTranslator().find(token);
		} else if (token == "arg") {
			lex.next(true);
			name_ = lex.getString();
		} else if (token == "\\end_inset")
			break;
	}	
	if (token != "\\end_inset") {
		lex.printError("Missing \\end_inset at this point");
		throw ExceptionMessage(WarningException,
			_("Missing \\end_inset at this point."),
			from_utf8(token));
	}
	updateInfo();
}