IO_METHOD(IoObject, installPrefix)
{

	char acPath[256];
	char root[256];
	if( GetModuleFileName( NULL, acPath, 256 ) != 0)
	{
		// guaranteed file name of at least one character after path
		strcpy(( strrchr( acPath, '\\' ) ), "\\..\\");
		_fullpath(root,acPath,256);
	}

	return IoState_symbolWithCString_(IOSTATE, root);
}