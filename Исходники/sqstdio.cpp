SQInteger sqstd_ftell(SQFILE file)
{
	return ftell((FILE *)file);
}