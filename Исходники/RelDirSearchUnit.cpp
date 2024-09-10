//---------------------------------------------------------------------------
bool __fastcall TRelDirSearchForm::GetFileList(AnsiString folder)
{
	try
	{
		GetFileList(folder, folder.Length());
	}
	catch(...)
	{
		return false;
	}
	return true;
}