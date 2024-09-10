	void cRedirectConsole::ListHead(ostream *os)
	{
		(*os) << "\r\n ";
		(*os) << setw(10) << setiosflags(ios::left) << toUpper(_("Count"));
		(*os) << setw(35) << setiosflags(ios::left) << toUpper(_("Address"));
		(*os) << setw(35) << setiosflags(ios::left) << toUpper(_("Type"));
		(*os) << toUpper(_("Status")) << "\r\n";
		(*os) << " " << string(30 + 25 + 25, '=');
	}