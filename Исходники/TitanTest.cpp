void WONQueryServices(const char *pPath)
{
	GetDirOpPtr cGetDir = new GetDirOp(WONGetCurrentServerContext(g_lWONServerList));

	cGetDir->SetPath(g_sWONCurPath + Make_wstring("/") + Make_wstring(pPath));
	cGetDir->SetFlags(
		DIR_GF_DECOMPSERVICES |
		DIR_GF_DECOMPRECURSIVE |
		DIR_GF_ADDTYPE |
		DIR_GF_ADDDISPLAYNAME |
		DIR_GF_ADDCREATED |
		DIR_GF_ADDTOUCHED |
		DIR_GF_ADDLIFESPAN |
		DIR_GF_SERVADDPATH |
		DIR_GF_SERVADDNETADDR |
		DIR_GF_SERVADDNAME);
	cGetDir->Run(OP_MODE_BLOCK, OP_TIMEOUT_INFINITE);
	if (cGetDir->GetStatus() != WS_Success)
	{
		g_pLTCSBase->CPrint("Directory not found");
		return;
	}

	// Display everything
	const DirEntityList &cFullDir = cGetDir->GetDirEntityList();
	DirEntityList::const_iterator iFullDirEntry = cFullDir.begin();
	for (; iFullDirEntry != cFullDir.end(); ++iFullDirEntry)
	{
		const wchar_t *pName = (*iFullDirEntry)->mDisplayName.empty() ? (*iFullDirEntry)->mName.c_str() : (*iFullDirEntry)->mDisplayName.c_str();
		g_pLTCSBase->CPrint("  %ls%s%ls", (*iFullDirEntry)->mPath.c_str(), (*iFullDirEntry)->mPath.length() == 1 ? "" : "/", pName);
		g_pLTCSBase->CPrint("    Type : %s", (*iFullDirEntry)->IsService() ? "Service" : "Directory");
		g_pLTCSBase->CPrint("    Display Name : %ls", (*iFullDirEntry)->mDisplayName.c_str());
		g_pLTCSBase->CPrint("    Created : %d", (*iFullDirEntry)->mCreated);
		g_pLTCSBase->CPrint("    Touched : %d", (*iFullDirEntry)->mTouched);
		g_pLTCSBase->CPrint("    Lifespan : %d", (*iFullDirEntry)->mLifespan);
		g_pLTCSBase->CPrint("    Path : %ls", (*iFullDirEntry)->mPath.c_str());
		g_pLTCSBase->CPrint("    Net Addr : %s", (*iFullDirEntry)->GetNetAddrAsIP().GetHostAndPortString().c_str());
		g_pLTCSBase->CPrint("    Name : %ls", (*iFullDirEntry)->mName.c_str());
	}
	g_pLTCSBase->CPrint("  <END>");

	return;
}