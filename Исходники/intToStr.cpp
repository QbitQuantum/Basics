std::string intToStr(int n, std::string s)
{
	if ((n / 10) != 0) {
		s = intToStr((n / 10), s);
	}
	int intDigit = n % 10;
	char charDigit = intToChar(intDigit);

	s.append(1, charDigit);
	return s;
}