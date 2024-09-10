EIF_INTEGER eif_user_directory_name_ptr(EIF_FILENAME a_buffer, EIF_INTEGER a_count) {
#ifdef EIF_WINDOWS
	if (a_buffer && (a_count >= (MAX_PATH * sizeof(wchar_t)))) {
			/* Buffer is large enough for the call to SHGetFolderPathW. */
		if (SHGetSpecialFolderPathW (NULL, a_buffer, CSIDL_PERSONAL, TRUE)) {
			return (EIF_INTEGER) ((wcslen(a_buffer) + 1) * sizeof (wchar_t));
		} else {
			return 0;
		}
	} else {
			/* Buffer is NULL or not large enough we ask for more. */
		return MAX_PATH * sizeof(wchar_t);
	}
#else
	return 0;
#endif
}