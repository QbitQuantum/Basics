static BOOL test_ClosePrinter(struct torture_context *tctx,
			      HANDLE handle)
{
	torture_comment(tctx, "Testing ClosePrinter");

	if (!ClosePrinter(handle)) {
		char tmp[1024];
		sprintf(tmp, "failed to close printer, error was: %s\n",
			errstr(GetLastError()));
		torture_fail(tctx, tmp);
	}

	return TRUE;
}