static void segv_handler(int signum)
{
	const char msg[] = "\nerror: segmentation fault\n"
		"Please submit a full bug report with --debug if appropriate.\n";
	xwrite(STDERR_FILENO, msg, sizeof(msg) - 1);
	_Exit(signum);
}