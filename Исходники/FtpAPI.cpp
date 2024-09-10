BOOL FtpRenameFile(Connection *Connect,LPCSTR lpszExisting,LPCSTR lpszNew)
{
	String Command;
	Assert(Connect && "FtpRenameFile");
	Connect->CacheReset();
	Command.printf("ren \x1%s\x1 \x1%s\x1",lpszExisting,lpszNew);
	return Connect->ProcessCommand(Command);
}