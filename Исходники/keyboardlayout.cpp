bool
KeyboardLayout::_SubstituteVariables(BString& term, VariableMap& variables,
	BString& unknown)
{
	while (true) {
		int32 index = term.FindFirst('$');
		if (index < 0)
			break;

		// find variable name

		VariableMap::iterator iterator = variables.begin();
		VariableMap::iterator best = variables.end();
		int32 bestLength = 0;

		for (; iterator != variables.end(); iterator++) {
			const BString& name = iterator->first;
			if (!name.Compare(&term[index], name.Length())
				&& name.Length() > bestLength) {
				best = iterator;
				bestLength = name.Length();
			}
		}

		if (best != variables.end()) {
			// got one, replace it
			term.Remove(index, bestLength);
			term.Insert(best->second.String(), index);
		} else {
			// variable has not been found
			unknown = &term[index];
			int32 length = 1;
			while (isalpha(unknown[length])) {
				length++;
			}
			unknown.Truncate(length);
			return false;
		}
	}

	return true;
}