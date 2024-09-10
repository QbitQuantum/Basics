BString
HaikuMailFormatFilter::_ExtractName(const BString& from)
{
	// extract name from something like "name" <*****@*****.**>
	// if name is empty return the mail address without "<>"

	BString name;
	int32 emailStart = from.FindFirst("<");
	if (emailStart < 0) {
		name = from;
		return name.Trim();
	}

	from.CopyInto(name, 0, emailStart);
	name.Trim();
	if (name.Length() >= 2) {
		if (name[name.Length() - 1] == '\"')
			name.Truncate(name.Length() - 1, true);
		if (name[0] == '\"')
			name.Remove(0, 1);
		name.Trim();
	}
	if (name != "")
		return name;

	// empty name extract email address
	name = from;
	name.Remove(0, emailStart + 1);
	name.Trim();
	if (name.Length() < 1)
		return from;
	if (name[name.Length() - 1] == '>')
		name.Truncate(name.Length() - 1, true);
	name.Trim();
	return name;
}