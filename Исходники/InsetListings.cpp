void InsetListings::latex(otexstream & os, OutputParams const & runparams) const
{
	string param_string = params().params();
	// NOTE: I use {} to quote text, which is an experimental feature
	// of the listings package (see page 25 of the manual)
	bool const isInline = params().isInline();
	// get the paragraphs. We can not output them directly to given odocstream
	// because we can not yet determine the delimiter character of \lstinline
	docstring code;
	docstring uncodable;
	ParagraphList::const_iterator par = paragraphs().begin();
	ParagraphList::const_iterator end = paragraphs().end();

	bool encoding_switched = false;
	Encoding const * const save_enc = runparams.encoding;

	if (!runparams.isFullUnicode()
	    && !runparams.encoding->hasFixedWidth()) {
		// We need to switch to a singlebyte encoding, since the
		// listings package cannot deal with multi-byte-encoded
		// glyphs (not needed with full-unicode aware backends
		// such as XeTeX).
		Language const * const outer_language =
			(runparams.local_font != 0) ?
				runparams.local_font->language()
				: buffer().params().language;
		// We try if there's a singlebyte encoding for the current
		// language; if not, fall back to latin1.
		Encoding const * const lstenc =
			(outer_language->encoding()->hasFixedWidth()) ?
				outer_language->encoding() 
				: encodings.fromLyXName("iso8859-1");
		switchEncoding(os.os(), buffer().params(), runparams, *lstenc, true);
		runparams.encoding = lstenc;
		encoding_switched = true;
	}

	while (par != end) {
		pos_type siz = par->size();
		bool captionline = false;
		for (pos_type i = 0; i < siz; ++i) {
			if (i == 0 && par->isInset(i) && i + 1 == siz)
				captionline = true;
			// ignore all struck out text and (caption) insets
			if (par->isDeleted(i) || par->isInset(i))
				continue;
			char_type c = par->getChar(i);
			// we can only output characters covered by the current
			// encoding!
			try {
				if (runparams.encoding->encodable(c))
					code += c;
				else if (runparams.dryrun) {
					code += "<" + _("LyX Warning: ")
					   + _("uncodable character") + " '";
					code += docstring(1, c);
					code += "'>";
 				} else
					uncodable += c;
			} catch (EncodingException & /* e */) {
 				if (runparams.dryrun) {
					code += "<" + _("LyX Warning: ")
					   + _("uncodable character") + " '";
					code += docstring(1, c);
					code += "'>";
 				} else
					uncodable += c;
			}
		}
		++par;
		// for the inline case, if there are multiple paragraphs
		// they are simply joined. Otherwise, expect latex errors.
		if (par != end && !isInline && !captionline)
			code += "\n";
	}
	if (isInline) {
		char const * delimiter = lstinline_delimiters;
		for (; delimiter != '\0'; ++delimiter)
			if (!contains(code, *delimiter))
				break;
		// This code piece contains all possible special character? !!!
		// Replace ! with a warning message and use ! as delimiter.
		if (*delimiter == '\0') {
			docstring delim_error = "<" + _("LyX Warning: ")
				+ _("no more lstline delimiters available") + ">";
			code = subst(code, from_ascii("!"), delim_error);
			delimiter = lstinline_delimiters;
			if (!runparams.dryrun) {
				// FIXME: warning should be passed to the error dialog
				frontend::Alert::warning(_("Running out of delimiters"),
				_("For inline program listings, one character must be reserved\n"
				  "as a delimiter. One of the listings, however, uses all available\n"
				  "characters, so none is left for delimiting purposes.\n"
				  "For the time being, I have replaced '!' by a warning, but you\n"
				  "must investigate!"));
			}
		}
		if (param_string.empty())
			os << "\\lstinline" << *delimiter;
		else
			os << "\\lstinline[" << from_utf8(param_string) << "]" << *delimiter;
                os << code
                   << *delimiter;
	} else {
		OutputParams rp = runparams;
		rp.moving_arg = true;
		docstring const caption = getCaption(rp);
		if (param_string.empty() && caption.empty())
			os << breakln << "\\begin{lstlisting}\n";
		else {
			os << breakln << "\\begin{lstlisting}[";
			if (!caption.empty()) {
				os << "caption={" << caption << '}';
				if (!param_string.empty())
					os << ',';
			}
			os << from_utf8(param_string) << "]\n";
		}
		os << code << breakln << "\\end{lstlisting}\n";
	}

	if (encoding_switched){
		// Switch back
		switchEncoding(os.os(), buffer().params(), runparams, *save_enc, true);
		runparams.encoding = save_enc;
	}

	if (!uncodable.empty()) {
		// issue a warning about omitted characters
		// FIXME: should be passed to the error dialog
		frontend::Alert::warning(_("Uncodable characters in listings inset"),
			bformat(_("The following characters in one of the program listings are\n"
				  "not representable in the current encoding and have been omitted:\n%1$s."),
			uncodable));
	}
}