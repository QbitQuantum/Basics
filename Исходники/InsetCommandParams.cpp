void InsetCommandParams::Read(Lexer & lex, Buffer const * buffer)
{
	lex.setContext("InsetCommandParams::read");
	lex >> insetName(insetCode_).c_str();
	lex >> "LatexCommand";
	lex >> cmdName_;
	if (!isCompatibleCommand(insetCode_, cmdName_)) {
		lex.printError("Incompatible command name " + cmdName_ + ".");
		throw ExceptionMessage(WarningException, _("InsetCommandParams Error: "),
		                       _("Incompatible command name."));
	}

	info_ = findInfo(insetCode_, cmdName_);
	
	string token;
	while (lex.isOK()) {
		lex.next();
		token = lex.getString();
		if (token == "\\end_inset")
			break;
		if (token == "preview") {
			lex.next();
			preview_ = lex.getBool();
			continue;
		}
		if (info_.hasParam(token)) {
			lex.next(true);
			docstring data = lex.getDocString();
			if (buffer && token == "filename") {
				data = from_utf8(buffer->includedFilePath(to_utf8(data)));
			} else if (buffer && token == "bibfiles") {
				int i = 0;
				docstring newdata;
				docstring bib = support::token(data, ',', i);
				while (!bib.empty()) {
					bib = from_utf8(buffer->includedFilePath(to_utf8(bib), "bib"));
					if (!newdata.empty())
						newdata.append(1, ',');
					newdata.append(bib);
					bib = support::token(data, ',', ++i);
				}
				data = newdata;
			} else if (buffer && token == "options") {
				data = from_utf8(buffer->includedFilePath(to_utf8(data), "bst"));
			}
			params_[token] = data;
		} else {
			lex.printError("Unknown parameter name `$$Token' for command " + cmdName_);
			throw ExceptionMessage(WarningException,
				_("InsetCommandParams: ") + from_ascii(cmdName_),
				_("Unknown parameter name: ") + from_utf8(token));
		}
	}
	if (token != "\\end_inset") {
		lex.printError("Missing \\end_inset at this point. "
			       "Read: `$$Token'");
		throw ExceptionMessage(WarningException,
			_("InsetCommandParams Error: "),
			_("Missing \\end_inset at this point: ") + from_utf8(token));
	}
}