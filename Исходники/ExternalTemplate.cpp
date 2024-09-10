void Template::readTemplate(Lexer & lex)
{
	enum {
		TO_GUINAME = 1,
		TO_HELPTEXT,
		TO_INPUTFORMAT,
		TO_FILTER,
		TO_AUTOMATIC,
		TO_PREVIEW,
		TO_TRANSFORM,
		TO_FORMAT,
		TO_END
	};

	LexerKeyword templateoptiontags[] = {
		{ "automaticproduction", TO_AUTOMATIC },
		{ "filefilter", TO_FILTER },
		{ "format", TO_FORMAT },
		{ "guiname", TO_GUINAME },
		{ "helptext", TO_HELPTEXT },
		{ "inputformat", TO_INPUTFORMAT },
		{ "preview", TO_PREVIEW },
		{ "templateend", TO_END },
		{ "transform", TO_TRANSFORM }
	};

	PushPopHelper pph(lex, templateoptiontags);
	lex.setContext("Template::readTemplate");

	string token;
	while (lex.isOK()) {
		switch (lex.lex()) {
		case TO_GUINAME:
			lex.next(true);
			guiName = lex.getString();
			break;

		case TO_HELPTEXT:
			helpText = lex.getLongString("HelpTextEnd");
			break;

		case TO_INPUTFORMAT:
			lex.next(true);
			inputFormat = lex.getString();
			break;

		case TO_FILTER:
			lex.next(true);
			fileRegExp = lex.getString();
			break;

		case TO_AUTOMATIC:
			lex.next();
			automaticProduction = lex.getBool();
			break;

		case TO_PREVIEW:
			lex >> token;
			if (token == "InstantPreview")
				preview_mode = PREVIEW_INSTANT;
			else if (token == "Graphics")
				preview_mode = PREVIEW_GRAPHICS;
			else
				preview_mode = PREVIEW_OFF;
			break;

		case TO_TRANSFORM: {
			lex >> token;
			TransformID id = transformIDTranslator().find(token);
			if (int(id) == -1)
				LYXERR0("Transform " << token << " is not recognized");
			else
				transformIds.push_back(id);
			break;
		}

		case TO_FORMAT:
			lex.next(true);
			formats[lex.getString()].readFormat(lex);
			break;

		case TO_END:
			return;

		default:
			lex.printError("external::Template::readTemplate: "
				       "Wrong tag: $$Token");
			LASSERT(false, /**/);
			break;
		}
	}
}