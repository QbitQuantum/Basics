void FilePanels::GoToFile(const wchar_t *FileName)
{
	if (FirstSlash(FileName))
	{
		string ADir,PDir;
		Panel *PassivePanel = GetAnotherPanel(ActivePanel);
		int PassiveMode = PassivePanel->GetMode();

		if (PassiveMode == NORMAL_PANEL)
		{
			PassivePanel->GetCurDir(PDir);
			AddEndSlash(PDir);
		}

		int ActiveMode = ActivePanel->GetMode();

		if (ActiveMode==NORMAL_PANEL)
		{
			ActivePanel->GetCurDir(ADir);
			AddEndSlash(ADir);
		}

		string strNameFile = PointToName(FileName);
		string strNameDir = FileName;
		CutToSlash(strNameDir);
		/* $ 10.04.2001 IS
		     Не делаем SetCurDir, если нужный путь уже есть на открытых
		     панелях, тем самым добиваемся того, что выделение с элементов
		     панелей не сбрасывается.
		*/
		BOOL AExist=(ActiveMode==NORMAL_PANEL) && !StrCmpI(ADir,strNameDir);
		BOOL PExist=(PassiveMode==NORMAL_PANEL) && !StrCmpI(PDir,strNameDir);

		// если нужный путь есть на пассивной панели
		if (!AExist && PExist)
			ProcessKey(KEY_TAB);

		if (!AExist && !PExist)
			ActivePanel->SetCurDir(strNameDir,TRUE);

		ActivePanel->GoToFile(strNameFile);
		// всегда обновим заголовок панели, чтобы дать обратную связь, что
		// Ctrl-F10 обработан
		ActivePanel->SetTitle();
	}
}