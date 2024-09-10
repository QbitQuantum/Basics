//---------------------------------------------------------------------------------
void FTPHost::Init(void)
{
	Log(("FTPHost::Init %p",this));
	memset(this,0,sizeof(*this));
	Size         = sizeof(*this);
	ExtCmdView   = Opt.ExtCmdView;
	IOBuffSize   = Opt.IOBuffSize;
	PassiveMode  = Opt.PassiveMode;
	ProcessCmd   = Opt.ProcessCmd;
	UseFirewall  = Opt.Firewall[0] != 0;
	FFDup        = Opt.FFDup;
	UndupFF      = Opt.UndupFF;
	DecodeCmdLine= TRUE;
	ServerType   = FTP_TYPE_DETECT;
	StrCpy(ListCMD, "LIST -la", ARRAYSIZE(ListCMD));
}