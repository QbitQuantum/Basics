TMatchResults TStaticTemplateMatcher::MatchStream(ICharStream &stream) {
	used = true;
	std::vector<TOccurance> ans;
	size_t pos = 0;
	currentnode = weak_ptr<TTrieNode>(getroot());
	if (!getroot()->terminal_.empty()) 
		for (TStringID &templateid: getroot()->terminal_)
			ans.push_back(std::make_pair(0,templateid));
	while (!stream.IsEmpty()) {
		char newchar=stream.GetChar();
		if (static_cast<int>(newchar) < 32 || static_cast<int>(newchar) > 255) 
			throw std::logic_error("Character out of range");
		Handlesymbol(newchar, ans, pos);
		pos++;
	}
	return ans;
}