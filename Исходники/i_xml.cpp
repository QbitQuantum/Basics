int CIXml::getIntProperty(xmlNodePtr node, const char *property, int defaultValue)
{
	CSString s;
	bool b;

	b=getPropertyString(s,node,property);
	if (b==false)
		return defaultValue;

	s=s.strip();
	sint val=s.atoi();
	if (val==0 && s!="0")
	{
		nlwarning("bad integer value: %s",s.c_str());
		return defaultValue;
	}

	return val;
}