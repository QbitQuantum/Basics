ConsoleTitle::~ConsoleTitle()
{
	CriticalSectionLock Lock(TitleCS);
	const FARString &strTitleAddons = GetFarTitleAddons();
	size_t OldLen = strOldTitle.GetLength();
	size_t AddonsLen = strTitleAddons.GetLength();

	if (AddonsLen <= OldLen)
	{
		if (!StrCmpI(strOldTitle.CPtr()+OldLen-AddonsLen, strTitleAddons))
			strOldTitle.SetLength(OldLen-AddonsLen);
	}

	ConsoleTitle::SetFarTitle(strOldTitle, true);
}