			int word_separator::default_word_type(utf32_point c) {
				if (iswspace(c)) return 0;
				else if (iswalnum(c)) return 1;
				else if (iswpunct(c)) return 2;
				else return 3;
			}