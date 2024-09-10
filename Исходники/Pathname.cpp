void BasicPathName<TChar>::internalCanonicalizePath(const char* srcPath, BasicPathName<char>* outPath) const
{
	char tmpPath[LN_MAX_PATH + 1] = { 0 };
	char* canonPath;
#ifdef _WIN32
	canonPath = _fullpath(tmpPath, srcPath, LN_MAX_PATH);
#else
	canonPath = realpath(mPath.c_str(), pathbuf);
#endif
	if (canonPath == NULL) {	// 変換失敗
		*outPath = BasicPathName<char>();
	}
	else {
		*outPath = BasicPathName<char>(tmpPath);
	}
}