static int nextToken (InputBuffer& buf) {
	buf.skipWhitespace();

	char r = *buf;
	if (r == '@')  // special command
		return CT_COMMAND;
	else if(isalpha (r))
		return CT_IDENT;
	else if(isdigit (r) || r == '.' || r == '-')
		return CT_NUMERIC;
	else if(r == '"')
		return CT_LITERAL;
	else if(r == '{')
		return CT_LIST;
	else if(r == ',')
		return CT_COMMA;

	throw ContentException(SPrintf("Unexpected character '%c'. ", r) + buf.location());
}