bool Counter::read(Lexer & lex)
{
	enum {
		CT_WITHIN = 1,
		CT_LABELSTRING,
		CT_LABELSTRING_APPENDIX,
		CT_PRETTYFORMAT,
		CT_END
	};

	LexerKeyword counterTags[] = {
		{ "end", CT_END },
		{ "labelstring", CT_LABELSTRING },
		{ "labelstringappendix", CT_LABELSTRING_APPENDIX },
		{ "prettyformat", CT_PRETTYFORMAT },
		{ "within", CT_WITHIN }
	};

	lex.pushTable(counterTags);

	bool getout = false;
	while (!getout && lex.isOK()) {
		int le = lex.lex();
		switch (le) {
			case Lexer::LEX_UNDEF:
				lex.printError("Unknown counter tag `$$Token'");
				continue;
			default: 
				break;
		}
		switch (le) {
			case CT_WITHIN:
				lex.next();
				master_ = lex.getDocString();
				if (master_ == "none")
					master_.erase();
				break;
			case CT_PRETTYFORMAT:
				lex.next();
				prettyformat_ = lex.getDocString();
				break;
			case CT_LABELSTRING:
				lex.next();
				labelstring_ = lex.getDocString();
				labelstringappendix_ = labelstring_;
				break;
			case CT_LABELSTRING_APPENDIX:
				lex.next();
				labelstringappendix_ = lex.getDocString();
				break;
			case CT_END:
				getout = true;
				break;
		}
	}

	// Here if have a full counter if getout == true
	if (!getout)
		LYXERR0("No End tag found for counter!");
	lex.popTable();
	return getout;
}