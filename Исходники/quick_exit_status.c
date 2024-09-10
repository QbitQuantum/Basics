int
main(int argc, const char *argv[])
{
	int status;

	if (argc != 2)
		abort();

	status = atoi(argv[1]);
	quick_exit(status);
	abort();
}