int
_start (int a1, int a2)
{
	char buf[100];

	for (;;) {
		printf ("sendexample> ");
		lineinput (buf, 100);
		switch (buf[0]) {
		case 'h':
			print_help (buf);
			break;
		case 's':
			sendex (buf);
			break;
		case 'q':
			exitprocess (0);
			break;
		default:
			command_error ();
			break;
		}
	}
}