/* main, menu */
void quit (void) {
	int choice;

	choice = getchoice (ppid == 1, " Demos Commander ",
		ppid == 1 ? "Do you want to log out ?" :
		"Do you want to quit the Demos Commander ?",
		NULL, " Yes ", " No ", " Exec shell ");
	if (choice == 0)
		quitdeco ();
	if (choice == 2) {
		/* exec shell */
		VClear ();
		VSync ();
		v.VClose();
		execle (ABSSHELL, SHELL, "-i", NULL, EnvVector);
		exit (0);
	}
	/* else stay here */
}