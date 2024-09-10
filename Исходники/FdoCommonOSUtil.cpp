int FdoCommonOSUtil::ismbstrail(const unsigned char *string, const unsigned char *current)
{
#ifdef _WIN32
    return _ismbstrail(string, current);
#else // _WIN32
    return FdoCommonOSUtil::ismbslead(string, current)==-1 ? 0 : -1;
#endif
}