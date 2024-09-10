std::string InputBuffer::parseIdent ()
{
	std::string name;

	if(isalnum (get()))
	{
		name += get();
		for (next(); isalnum (get()) || get() == '_' || get() == '-'; next())
			name += get();

		return name;
	}
	else
		throw ContentException(SPrintf("%s: Expecting an identifier instead of '%c'\n", location().c_str(), get()));
}