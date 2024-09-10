// ru: Удаление файла (аналог "remove")
// en: Deleting of file (analogue "remove")
int MP_Platform_WIN_POSIX::RemoveFile(const char* file)
{
	#ifdef _WINDOWS

	return _wremove(utf8_to_wchar(file));

	#else

	return remove(file);

	#endif
}