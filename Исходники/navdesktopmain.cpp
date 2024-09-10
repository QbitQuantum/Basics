void CNavDesktopModule::_UpdateSelf()
{
	//升级
	_beginthreadex(NULL, 0, UpdateSelfProc, this, 0, NULL);
}