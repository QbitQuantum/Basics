// Returns file path including the trailing path separator symbol.
void GetFilePath(const wchar *FullName,wchar *Path,int MaxLength)
{
  size_t PathLength=Min(MaxLength-1,PointToName(FullName)-FullName);
  strncpyw(Path,FullName,PathLength);
  Path[PathLength]=0;
}