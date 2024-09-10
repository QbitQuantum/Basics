ostream& operator<<(ostream& os, const Student& student) {
	// print ID
	os << "ID: ";
	if (student.id() == Student::uninitialized_id) { os << "Undefined"; }
	else { os << student.id(); }

	os << "; Gender: " << student.gender();
	os << "; Ethnicity: " << student.ethnicity();
	os << "; School: " << student.school();
	os << "; Transfer status: " << (student.transfer() ? "Transfer" :
		"Non-transfer");

	// print first term
	os << "; First term: ";
	if (student.first_term() == Student::uninitialized_term)
	{ os << "Undefined"; }
	else { os << student.first_term(); }
	os << "; Major(s): ";
	if (student.major1()) { os << student.GetMajor1Description(); }
	if (student.major2()) { os << ", " << student.GetMajor2Description(); }
	if (!student.courses_taken_.empty()) {
		os << "; Classes: ";
		transform(student.courses_taken_.cbegin(),
				  --student.courses_taken_.cend(),
				  ostream_iterator<Course::Id>{os, ", "},
				  [](const Course* course) { return course->GetId(); });
		os << (*student.courses_taken_.rbegin())->GetId();
	}
	return os;
}