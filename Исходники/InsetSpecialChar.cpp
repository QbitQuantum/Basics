// This function will not be necessary when lyx3
void InsetSpecialChar::read(Lexer & lex)
{
	lex.next();
	string const command = lex.getString();

	if (command == "\\-")
		kind_ = HYPHENATION;
	else if (command == "\\textcompwordmark{}")
		kind_ = LIGATURE_BREAK;
	else if (command == "\\@.")
		kind_ = END_OF_SENTENCE;
	else if (command == "\\ldots{}")
		kind_ = LDOTS;
	else if (command == "\\menuseparator")
		kind_ = MENU_SEPARATOR;
	else if (command == "\\slash{}")
		kind_ = SLASH;
	else if (command == "\\nobreakdash-")
		kind_ = NOBREAKDASH;
	else
		lex.printError("InsetSpecialChar: Unknown kind: `$$Token'");
}