	size_t add_string(const size_t vertex, const StringView& s, const bool add_substrings = false)
		// extend Trie by one string
		// REQUIRE: all chars in interval [0..alphabet_size]
	{
		size_t v = vertex;
		for (size_t i = 0; i < s.length(); ++i) {
			v = add_char(v, s[i], add_substrings || i == s.length() - 1);
		}
		return v;
	}