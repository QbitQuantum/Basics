std::string osgDB::convertToLowerCase(const std::string& str)
{
    std::string lowcase_str(str);
    for(std::string::iterator itr=lowcase_str.begin();
        itr!=lowcase_str.end();
        ++itr)
    {
        *itr = tolower(*itr);
    }
    return lowcase_str;
}