void
DBListBuilder::GetDBs(HWND hwndcombo, wyBool isrefreshtrue)
{
	 // now we call the enum function and fill the combo with the databases.
	//Fetching the databases from MySQL(by executing Show databases)
	if(isrefreshtrue == wyTrue)
		EnumChildWindows(pGlobals->m_hwndclient, DBListBuilder::GetDBFromServers, (LPARAM)hwndcombo);
	else
		//Fetching the databases from object browser
		EnumChildWindows(pGlobals->m_hwndclient, DBListBuilder::GetDBFromActiveWins, (LPARAM)hwndcombo);
}