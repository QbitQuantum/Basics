void InsetText::read(Lexer & lex)
{
	clear();

	// delete the initial paragraph
	Paragraph oldpar = *paragraphs().begin();
	paragraphs().clear();
	ErrorList errorList;
	lex.setContext("InsetText::read");
	bool res = text_.read(lex, errorList, this);

	if (!res)
		lex.printError("Missing \\end_inset at this point. ");

	// sanity check
	// ensure we have at least one paragraph.
	if (paragraphs().empty())
		paragraphs().push_back(oldpar);
	// Force default font, if so requested
	// This avoids paragraphs in buffer language that would have a
	// foreign language after a document language change, and it ensures
	// that all new text in ERT and similar gets the "latex" language,
	// since new text inherits the language from the last position of the
	// existing text.  As a side effect this makes us also robust against
	// bugs in LyX that might lead to font changes in ERT in .lyx files.
	fixParagraphsFont();
}