void MultipleChoiceValue::normalForm() {
	String val = value->toString();
	// which choices are active?
	vector<bool> seen(field().choices->lastId());
	for (size_t pos = 0 ; pos < val.size() ; ) {
		if (val.GetChar(pos) == _(' ')) {
			++pos; // ingore whitespace
		} else {
			// does this choice match the one asked about?
			size_t end = val.find_first_of(_(','), pos);
			if (end == String::npos) end = val.size();
			// find this choice
			for (size_t i = 0 ; i < seen.size() ; ++i) {
				if (is_substr(val, pos, field().choices->choiceName((int)i))) {
					seen[i] = true;
					break;
				}
			}
			pos = end + 1;
		}
	}
	// now put them back in the right order
	val.clear();
	for (size_t i = 0 ; i < seen.size() ; ++i) {
		if (seen[i]) {
			if (!val.empty()) val += _(", ");
			val += field().choices->choiceName((int)i);
		}
	}
	// empty choice name
	if (val.empty()) {
		val = field().empty_choice;
	}
	// store
	value = with_defaultness_of(value, to_script(val));
}