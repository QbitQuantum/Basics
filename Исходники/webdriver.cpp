int wdAddStringScriptArg(ScriptArgs* scriptArgs, const wchar_t* arg) 
{
	std::wstring value(arg);

	CComVariant dest(arg);
	LONG index = scriptArgs->currentIndex;
	SafeArrayPutElement(scriptArgs->args, &index, &dest);

	scriptArgs->currentIndex++;

	return SUCCESS;
}