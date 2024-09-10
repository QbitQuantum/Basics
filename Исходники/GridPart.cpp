ostream& operator<<(ostream& output, GridPart* part) {
	if (part == NULL) {
		output << "{n}";
		return output;
	}
	for (int s=0; s<(int)part->size(); s++) {
		GridStaff* staff = part->at(s);
		output << "(s" << s << ":)";
		if (staff == NULL) {
			output << "{n}";
			continue;
		}
		for (int t=0; t<(int)staff->size(); t++) {
			GridVoice* gt = staff->at(t);
			output << "(v" << t << ":)";
			if (gt == NULL) {
				output << "{n}";
				continue;
			} else {
				HTp token = gt->getToken();
				if (token == NULL) {
					output << "{n}";
				} else {
					output << " \"" << *token << "\" ";
				}
			}
		}
	}
	return output;
}