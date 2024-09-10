bool GenericXMLParser::ParseAttribute(String &name, String &value)
{
	StartTrace(GenericXMLParser.ParseAttribute);
	name = ParseName();
	name.ToLower(); // XHTML conformance all attribute names are lower case
	Trace("attribute name:" << name);
	value = "";
	SkipWhitespace();
	int c = Peek();
	if (c != '=') {
		return false;
	}
	c = Get();
	(void)c;
	SkipWhitespace();
	value = ParseValue();
	return true;
	// otherwise it is a syntax error, we just ignore silently for now.
}