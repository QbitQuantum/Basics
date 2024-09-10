void TestPropSheetExt::FileNotFound()
{
	try
	{
		TestExecutePropSheetExt(_T("filenotfound.vvv"));
	}
	catch (const _com_error&)
	{
		// expect failed HRESULT.
		return;
	}

	_com_raise_error(E_FAIL);
}