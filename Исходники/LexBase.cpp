bool
LexBase::isIdentifierChar(const MBChar & mbCh)
{
	wchar_t				wCh;
	bool				result;

	wCh = mbCh.getWChar();
	result =   (::iswalpha(wCh) != 0) // letter
		|| (::iswdigit(wCh) != 0) // digit
		|| mbCh == '-'   // dash
		|| mbCh == '_'   // underscore
		|| mbCh == '.'   // dot
		|| mbCh == ':'   // For C++ nested names, e.g., Foo::Bar
		|| mbCh == '$'   // For mangled names of Java nested classes
		|| mbCh == '?'   // For Ruby identifiers, e.g., found?
		|| mbCh == '/'   // For URLs, e.g., http://foo.com/bar/
		|| mbCh == '\\'  // For Windows directory names
		;
	return result;
}