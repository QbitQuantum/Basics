	std::vector<lstring> convert_split_words(const lstring &lt) {
		std::vector<lstring> ret;

		UBreakIterator* bi;
		int prev = -1, pos;

		UErrorCode err = U_ZERO_ERROR;
		bi = ubrk_open(UBRK_WORD, get_locale(), (UChar *)lt.data(), lt.size(), &err);
		if (U_FAILURE(err))
			return ret;

		pos = ubrk_first(bi);
		while (pos != UBRK_DONE) {
			int rules = ubrk_getRuleStatus(bi);
			if ((rules == UBRK_WORD_NONE) || (prev == -1)) {
				prev = pos;
			} else {
				ret.emplace_back(lt.substr(prev, pos - prev));

				prev = -1;
			}

			pos = ubrk_next(bi);
		}

		ubrk_close(bi);

		return ret;
	}