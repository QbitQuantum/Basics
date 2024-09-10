//==============================================================================
Error removeDirectory(const CString& dirname)
{
	Error err = ErrorCode::NONE;
	SHFILEOPSTRUCTA fileOperation;
	fileOperation.wFunc = FO_DELETE;
	fileOperation.pFrom = dirname.get();
	fileOperation.fFlags = FOF_NO_UI | FOF_NOCONFIRMATION;

	I result = SHFileOperationA(&fileOperation);
	if(result != 0) 
	{
		ANKI_LOGE("Could not delete directory %s", dirname.get());
		err = ErrorCode::FUNCTION_FAILED;
	}

	return err;
}