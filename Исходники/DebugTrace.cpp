void d_assert(char *str, char *file, int line)
{
	std::string msg = SPrintf("Assertion \"%s\" failed at line %d in \'%s\'\n", str, line, file);
	d_trace (msg.c_str());

	throw std::runtime_error(msg.c_str());
}