FskErr winTextAddFontFile(FskTextEngineState state, const char *path)
{
	FskErr err;
	WCHAR *nativePath = NULL;

	err = FskFilePathToNative(path, (char **)&nativePath);
	BAIL_IF_ERR(err);

	if (0 == AddFontResourceExW(nativePath, FR_PRIVATE, 0))
		BAIL(kFskErrOperationFailed);

bail:
	FskMemPtrDispose(nativePath);

	return err;
}