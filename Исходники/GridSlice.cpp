void GridSlice::transferTokens(HumdrumFile& outfile, bool recip) {
	HTp token;
	HumdrumLine* line = new HumdrumLine;
	GridVoice* voice;
	string empty = ".";

	if (recip) {
		if (isNoteSlice()) {
			token = createRecipTokenFromDuration(getDuration());
		} else if (isClefSlice()) {
			token = new HumdrumToken("*");
			empty = "*";
		} else if (isMeasureSlice()) {
			voice = this->at(0)->at(0)->at(0);
			token = new HumdrumToken((string)*voice->getToken());
//ggg
			empty = (string)*token;
		} else if (isInterpretationSlice()) {
			token = new HumdrumToken("*");
			empty = "*";
		} else {
			token = new HumdrumToken("55");
			empty = "!z";
		}
		line->appendToken(token);
	}

	// extract the Tokens from each part/staff
	int p; // part index
	int s; // staff index
	int v; // voice index

	for (p=(int)size()-1; p>=0; p--) {

		GridPart& part = *this->at(p);
		for (s=(int)part.size()-1; s>=0; s--) {
			GridStaff& staff = *part.at(s);
			if (staff.size() == 0) {
				// fix this later.  For now if there are no notes
				// on the staff, add a null token.  Fix so that
				// all open voices are given null tokens.
				token = new HumdrumToken(empty);
				line->appendToken(token);
			} else {
				for (v=0; v<(int)staff.size(); v++) {
					if (staff.at(v) && staff.at(v)->getToken()) {
						line->appendToken(staff.at(v)->getToken());
						staff.at(v)->forgetToken();
					} else if (!staff.at(v)) {
						token = new HumdrumToken(".z");
						line->appendToken(token);
					} else {
						token = new HumdrumToken(".b");
						line->appendToken(token);
					}
				}

			}
			int maxvcount = getVerseCount(p, s);
			int maxhcount = getHarmonyCount(p, s);
			transferSides(*line, staff, empty, maxvcount, maxhcount);
		}
		int maxhcount = getHarmonyCount(p);
		int maxvcount = getVerseCount(p, -1);
		transferSides(*line, part, empty, maxvcount, maxhcount);
	}

	outfile.appendLine(line);
}