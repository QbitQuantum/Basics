bool JavaString::operator==(const std::string& str) const {
	jsize len = Length();
	if(len != (jsize) str.length())
		return false;
	return str == Value();
}