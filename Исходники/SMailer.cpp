AppOctStrmContent::AppOctStrmContent(const MailString file_name)
    : _file_name(file_name)
{
    TCHAR drive[_MAX_DRIVE];
    TCHAR direc[_MAX_DIR];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
#ifdef _UNICODE
	_wsplitpath(file_name.c_str(), drive, direc, fname, ext);
#else
    _splitpath(file_name.c_str(), drive, direc, fname, ext);
#endif
    _name  = fname;
    _name += ext;
}