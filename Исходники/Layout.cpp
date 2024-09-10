void Layout::readLabelType(Lexer & lex)
{
	enum {
		LA_NO_LABEL = 1,
		LA_MANUAL,
		LA_ABOVE,
		LA_CENTERED,
		LA_STATIC,
		LA_SENSITIVE,
		LA_ENUMERATE,
		LA_ITEMIZE,
		LA_BIBLIO
	};


	LexerKeyword labelTypeTags[] = {
	  { "above",        LA_ABOVE },
		{ "bibliography", LA_BIBLIO },
		{ "centered",     LA_CENTERED },
		{ "enumerate",    LA_ENUMERATE },
		{ "itemize",      LA_ITEMIZE },
		{ "manual",       LA_MANUAL },
		{ "no_label",     LA_NO_LABEL },
		{ "sensitive",    LA_SENSITIVE },
		{ "static",       LA_STATIC }
	};

	PushPopHelper pph(lex, labelTypeTags);
	int le = lex.lex();
	switch (le) {
	case Lexer::LEX_UNDEF:
		lex.printError("Unknown labeltype tag `$$Token'");
		return;
	default: break;
	}
	switch (le) {
	case LA_NO_LABEL:
		labeltype = LABEL_NO_LABEL;
		break;
	case LA_MANUAL:
		labeltype = LABEL_MANUAL;
		break;
	case LA_ABOVE:
		labeltype = LABEL_ABOVE;
		break;
	case LA_CENTERED:
		labeltype = LABEL_CENTERED;
		break;
	case LA_STATIC:
		labeltype = LABEL_STATIC;
		break;
	case LA_SENSITIVE:
		labeltype = LABEL_SENSITIVE;
		break;
	case LA_ENUMERATE:
		labeltype = LABEL_ENUMERATE;
		break;
	case LA_ITEMIZE:
		labeltype = LABEL_ITEMIZE;
		break;
	case LA_BIBLIO:
		labeltype = LABEL_BIBLIO;
		break;
	}
}