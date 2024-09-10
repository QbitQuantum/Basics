void Datastore::removeRecord(const std::string& path) {

	auto tokens = _tokenizePath(path);
	if (tokens.empty()) { return; } // invalid path

	auto records = _recordsOnPath(tokens);
	if (records.empty()) { return; }
	if (!records.back()) { return; }

	// records array now has no null pointers

	// records and tokens correlate 1:1.
	// _root -> records[0] -> records[1] -> ...
	//      tokens[0] -> tokens[1] -> ...
	// The associations between parent and child are named.
	// The names are the tokens.

	records.pop_back();
	Record* parent = records.empty() ? &_root : records.back();
	parent->removeChild(tokens.back().c_str());
	tokens.pop_back();

	try {
		while (tokens.size() > 0) {
			if (parent->numChildren() == 0) {
				records.pop_back();
				parent = records.empty() ? &_root : records.back();
				parent->removeChild(tokens.back().c_str());
				tokens.pop_back();
			} else {
				break;
			}
		}
	} catch (std::exception& e) {
		Logf("%s", e.what());
	}
}