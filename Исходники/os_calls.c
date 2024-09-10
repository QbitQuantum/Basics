/* returns boolean */
int g_remove_dir(const char *dirname)
{
#if defined(_WIN32)
	return RemoveDirectoryA(dirname); // test this
#else
	return rmdir(dirname) == 0;
#endif
}