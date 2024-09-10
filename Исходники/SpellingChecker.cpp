static int startsWithCapital (const char32 *word) {
	return iswupper ((int) word [0]) || (word [0] == '\\' && iswupper ((int) word [1]));
}