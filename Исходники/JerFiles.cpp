void TJerFile::GetRelativePathAndName(const char *BeginDir,const char *Path,char **TheRelativePathAndName)
{
	BPath BeginPath(BeginDir);
	BPath PathPath(Path);
	string Begin(BeginPath.Path());
	string Chemin(PathPath.Path());
	string RelativePathBuffer("");
	string RelativePath("");
	for (uint32 ind=Begin.length();ind<Chemin.length();ind++)
	{
		RelativePathBuffer = RelativePathBuffer + Chemin[ind];
	}
	*TheRelativePathAndName = (char *)malloc(sizeof(char)*(RelativePathBuffer.length()+1));
	strcpy(*TheRelativePathAndName,RelativePathBuffer.c_str());
}