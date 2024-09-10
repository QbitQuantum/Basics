void CodeFile::output(const char* s, ...)
{
	PRINT_INDENT(file_, ind_);
	VFPRINTF(file_, s);
	fprintf(file_, "\n");
}