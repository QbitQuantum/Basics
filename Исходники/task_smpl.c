static void
cld_handler(int n)
{
	longjmp(jbuf, 1);
}