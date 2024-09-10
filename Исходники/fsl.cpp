int fsl_copy_with_parent(const CC_STRING& src, const CC_STRING& dst)
{
	CC_STRING ddir;
	const char *pos;
	int retval;

	pos = strrchr(dst.c_str(), '/');
	if(pos != NULL) {
		ddir.strcat(dst.c_str(), pos);
		retval = fsl_mkdir(ddir);
		if( retval != 0)
			return retval;
	}
	return fsl_copy(src, dst);
}