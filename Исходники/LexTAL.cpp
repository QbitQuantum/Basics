static void ColouriseTALDoc(unsigned int startPos, int length, int initStyle, WordList *keywordlists[],
	Accessor &styler) {

	styler.StartAt(startPos);

	int state = initStyle;
	if (state == SCE_C_CHARACTER)	// Does not leak onto next line
		state = SCE_C_DEFAULT;
	char chPrev = ' ';
	char chNext = styler[startPos];
	unsigned int lengthDoc = startPos + length;

	bool bInClassDefinition;

	int currentLine = styler.GetLine(startPos);
	if (currentLine > 0) {
		styler.SetLineState(currentLine, styler.GetLineState(currentLine-1));
		bInClassDefinition = (styler.GetLineState(currentLine) == 1);
	} else {
		styler.SetLineState(currentLine, 0);
		bInClassDefinition = false;
	}

	bool bInAsm = (state == SCE_C_REGEX);
	if (bInAsm)
		state = SCE_C_DEFAULT;

	styler.StartSegment(startPos);
	int visibleChars = 0;
	for (unsigned int i = startPos; i < lengthDoc; i++) {
		char ch = chNext;

		chNext = styler.SafeGetCharAt(i + 1);

		if ((ch == '\r' && chNext != '\n') || (ch == '\n')) {
			// Trigger on CR only (Mac style) or either on LF from CR+LF (Dos/Win) or on LF alone (Unix)
			// Avoid triggering two times on Dos/Win
			// End of line
			if (state == SCE_C_CHARACTER) {
				ColourTo(styler, i, state, bInAsm);
				state = SCE_C_DEFAULT;
			}
			visibleChars = 0;
			currentLine++;
			styler.SetLineState(currentLine, (bInClassDefinition ? 1 : 0));
		}

		if (styler.IsLeadByte(ch)) {
			chNext = styler.SafeGetCharAt(i + 2);
			chPrev = ' ';
			i += 1;
			continue;
		}

		if (state == SCE_C_DEFAULT) {
			if (isTALwordstart(ch)) {
				ColourTo(styler, i-1, state, bInAsm);
				state = SCE_C_IDENTIFIER;
			} else if (ch == '!' && chNext != '*') {
				ColourTo(styler, i-1, state, bInAsm);
				state = SCE_C_COMMENT;
			} else if (ch == '!' && chNext == '*') {
				ColourTo(styler, i-1, state, bInAsm);
				state = SCE_C_COMMENTDOC;
			} else if (ch == '-' && chNext == '-') {
				ColourTo(styler, i-1, state, bInAsm);
				state = SCE_C_COMMENTLINE;
			} else if (ch == '"') {
				ColourTo(styler, i-1, state, bInAsm);
				state = SCE_C_STRING;
			} else if (ch == '?' && visibleChars == 0) {
				ColourTo(styler, i-1, state, bInAsm);
				state = SCE_C_PREPROCESSOR;
			} else if (isTALoperator(ch)) {
				ColourTo(styler, i-1, state, bInAsm);
				ColourTo(styler, i, SCE_C_OPERATOR, bInAsm);
			}
		} else if (state == SCE_C_IDENTIFIER) {
			if (!isTALwordchar(ch)) {
				int lStateChange = classifyWordTAL(styler.GetStartSegment(), i - 1, keywordlists, styler, bInAsm);

				if(lStateChange == 1) {
					styler.SetLineState(currentLine, 1);
					bInClassDefinition = true;
				} else if(lStateChange == 2) {
					bInAsm = true;
				} else if(lStateChange == -1) {
					styler.SetLineState(currentLine, 0);
					bInClassDefinition = false;
					bInAsm = false;
				}

				state = SCE_C_DEFAULT;
				chNext = styler.SafeGetCharAt(i + 1);
				if (ch == '!' && chNext != '*') {
					state = SCE_C_COMMENT;
				} else if (ch == '!' && chNext == '*') {
					ColourTo(styler, i-1, state, bInAsm);
					state = SCE_C_COMMENTDOC;
				} else if (ch == '-' && chNext == '-') {
					state = SCE_C_COMMENTLINE;
				} else if (ch == '"') {
					state = SCE_C_STRING;
				} else if (isTALoperator(ch)) {
					ColourTo(styler, i, SCE_C_OPERATOR, bInAsm);
				}
			}
		} else {
			if (state == SCE_C_PREPROCESSOR) {
				if ((ch == '\r' || ch == '\n') && !(chPrev == '\\' || chPrev == '\r')) {
					ColourTo(styler, i-1, state, bInAsm);
					state = SCE_C_DEFAULT;
				}
			} else if (state == SCE_C_COMMENT) {
				if (ch == '!' || (ch == '\r' || ch == '\n') ) {
					ColourTo(styler, i, state, bInAsm);
					state = SCE_C_DEFAULT;
				}
			} else if (state == SCE_C_COMMENTDOC) {
				if (ch == '!' || (ch == '\r' || ch == '\n')) {
					if (((i > styler.GetStartSegment() + 2) || (
						(initStyle == SCE_C_COMMENTDOC) &&
						(styler.GetStartSegment() == static_cast<unsigned int>(startPos))))) {
							ColourTo(styler, i, state, bInAsm);
							state = SCE_C_DEFAULT;
					}
				}
			} else if (state == SCE_C_COMMENTLINE) {
				if (ch == '\r' || ch == '\n') {
					ColourTo(styler, i-1, state, bInAsm);
					state = SCE_C_DEFAULT;
				}
			} else if (state == SCE_C_STRING) {
				if (ch == '"') {
					ColourTo(styler, i, state, bInAsm);
					state = SCE_C_DEFAULT;
				}
			}
		}
        if (!isspacechar(ch))
            visibleChars++;
		chPrev = ch;
	}
	ColourTo(styler, lengthDoc - 1, state, bInAsm);
}