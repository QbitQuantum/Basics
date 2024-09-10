int64 TypeConvert::ToInt64(const char* str)
{
	if (!str)
		return 0;

	// todo:fix
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	return (int64)_atoi64(str);
#else
	return atoll(str);
#endif
}