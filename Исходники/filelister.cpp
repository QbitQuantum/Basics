static BOOL MyIsDirectory(const std::string& path)
{
#ifdef __BORLANDC__
    return (GetFileAttributes(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY);
#else
// See http://msdn.microsoft.com/en-us/library/bb773621(VS.85).aspx
    return PathIsDirectoryA(path.c_str());
#endif
}