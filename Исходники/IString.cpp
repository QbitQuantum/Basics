IString IString::upperCase(){
	std::string s = this->c_str();
	transform( s.begin(), s.end(), s.begin(), ::toupper );
	return IString(s.c_str());
}