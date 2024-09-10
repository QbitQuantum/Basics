void
xechoit(tchar **t)
{
#ifdef TRACE
	tprintf("TRACE- xechoit()\n");
#endif

	if (adrof(S_echo /* "echo" */)) {
		flush();
		haderr = 1;
		blkpr(t), Putchar('\n');
		haderr = 0;
	}
}