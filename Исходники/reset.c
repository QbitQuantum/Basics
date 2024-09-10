/* ARGSUSED */
static SIGVAL
abortReset (int n)
{
	Longjmp (resetJmp, 1);
}