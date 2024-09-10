void SuggestionGeneratorSoftHyphens::generate(SuggestionStatus * s) const {
	const size_t wlen = s->getWordLength();
	const wchar_t * word = s->getWord();
	const wchar_t * softHyphen = wmemchr(word, L'\u00AD', wlen);
	if (softHyphen) {
		wchar_t * buffer = new wchar_t[wlen];
		size_t j = 0;
		for (size_t i = 0; i < wlen; ++i) {
			if (word[i] != L'\u00AD') {
				buffer[j++] = word[i];
			}
		}
		buffer[j] = L'\0';
		SuggestionGeneratorCaseChange::suggestForBuffer(morAnalyzer, s, buffer, j);
		delete[] buffer;
	}
}