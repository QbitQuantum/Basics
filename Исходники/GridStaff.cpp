ostream& operator<<(ostream& output, GridStaff* staff) {
	if (staff == NULL) {
		output << "{n}";
		return output;
	}
	for (int t=0; t<(int)staff->size(); t++) {
		GridVoice* gt = staff->at(t);
		cout << "(v" << t << ":)";
		if (gt == NULL) {
			cout << "{gt:n}";
			continue;
		} else {
			HTp token = gt->getToken();
			if (token == NULL) {
				cout << "{n}";
			} else {
				cout << " \"" << *token << "\" ";
			}
		}
	}
	return output;
}