int
efile_mkdir(Efile_error* errInfo,	/* Where to return error codes. */
	    char* name)			/* Name of directory to create. */
{
    return check_error(_wmkdir((WCHAR *) name), errInfo);
}