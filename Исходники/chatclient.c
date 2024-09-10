void error(void)
{
	fprintf(stderr, "%s\n", "bad command\n"
		"syntax: [command] [optional recipient] [optional msg]");
}