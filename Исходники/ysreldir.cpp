static YSRESULT YsAnalyzeTemplate(StringClass &relPath,StringClass &path,StringClass &fromPath)
{
	StringClass moveUp;
	YsRemoveSamePartTemplate(path,fromPath);
	YsMoveUpwardTemplate(moveUp,fromPath);
	if(0<moveUp.Strlen())
	{
		relPath.MakeFullPathName(moveUp,path);
	}
	else
	{
		relPath=path;
	}
	return YSOK;
}