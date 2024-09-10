void Main ()
{
	int pid;

	if ((pid = Fork ()) == 0) {

		/* child executes here */

		Printf ("I am the child, my pid is %d\n", Getpid ());
        Exit();
	}

	Printf ("I am the parent, my pid is %d\n", Getpid ());
	Printf ("I just created a child process whose pid is %d\n", pid);
}