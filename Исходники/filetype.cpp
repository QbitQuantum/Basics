bool ExtractIfExistCommand(string &strCommandText)
{
	bool Result=true;
	const wchar_t *wPtrCmd=PrepareOSIfExist(strCommandText);

	// Во! Условие не выполнено!!!
	// (например, пока рассматривали менюху, в это время)
	// какой-то злобный чебурашка стер файл!
	if (wPtrCmd)
	{
		if (!*wPtrCmd)
		{
			Result=false;
		}
		else
		{
			size_t offset = wPtrCmd-strCommandText.CPtr();
			wchar_t *CommandText = strCommandText.GetBuffer();
			wchar_t *PtrCmd = CommandText+offset;
			// прокинем "if exist"
			wmemmove(CommandText+(*CommandText==L'@'?1:0),PtrCmd,StrLength(PtrCmd)+1);
			strCommandText.ReleaseBuffer();
		}
	}

	return Result;
}