void SendEmailThread(void *szUrl)
{
	ShellExecuteA(NULL, "open", (char*)szUrl, "", "", SW_SHOW);
	mir_free(szUrl);
	return;
}