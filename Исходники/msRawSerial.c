//_______________________________________________________________________
static void FatalError (const char *msg) 
{
	fprintf (stderr, "%s\n", msg);
	closeDriver (GetData());
	exit (1);
}