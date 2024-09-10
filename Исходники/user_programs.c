int _kill (int argc, char ** argv)
{
	int c = getC();
	printf("%c\n", c);
	if (argc > 1) {
		int pid = atoi(argv[1]);
		if (pid >= 0) {
			kill(2,pid);
		}
	}
	return 0;
}