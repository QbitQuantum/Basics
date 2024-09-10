unsigned int RvFindRegex::directoryCheck(const std::wstring& directory, const std::wstring& pathRoot) const
{
    if (pathRoot.empty())
        return DIRECTORY_DONTCARE;
    size_t dirLength = directory.length();
    if (dirLength > pathRoot.size())
    {
        if (boost::algorithm::istarts_with(directory,pathRoot))
            return DIRECTORY_INCLUDE;
        else
            return DIRECTORY_EXCLUDE;
    }
    if (boost::algorithm::istarts_with(pathRoot,directory))
        return DIRECTORY_INCLUDE;
    else
        return DIRECTORY_EXCLUDE;
}