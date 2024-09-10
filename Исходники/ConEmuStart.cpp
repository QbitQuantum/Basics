// ********************************************
CConEmuStart::CConEmuStart(CConEmuMain* pOwner)
{
	mp_ConEmu = pOwner;
	_ASSERTE(mp_ConEmu!=NULL);

	m_StartDetached = crb_Undefined;
	mb_ConEmuHere = false;
	mb_ForceQuitOnClose = false;
	isCurCmdList = false;
	SetDefaultCmd(L"far");
	mn_ShellExitCode = STILL_ACTIVE;

	ZeroStruct(ourSI);
	ourSI.cb = sizeof(ourSI);
	try
	{
		GetStartupInfoW(&ourSI);
	}
	catch(...)
	{
		ZeroStruct(ourSI);
	}
}