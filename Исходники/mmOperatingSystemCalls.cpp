void mmOperatingSystem::RemoveDir(mmString p_sDirName)
{
	int v_iRes = _wrmdir(p_sDirName.c_str());
	if(v_iRes != 0)
	{
		switch(errno)
		{
			case EACCES:
			{
				throw mmError(mmeFileIOPermissionToFileDenied);
			};
			case ENOENT:
			{
				throw mmError(mmeFileIONoSuchFileOrDirectory);
			};
			default:
			{
				throw mmError(mmeUnknownError);
			};
		};
	};
}