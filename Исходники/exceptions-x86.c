void win32_seh_cleanup()
{
	if (mono_old_win_toplevel_exception_filter)
		SetUnhandledExceptionFilter(mono_old_win_toplevel_exception_filter);
	RemoveVectoredExceptionHandler (mono_win_vectored_exception_handle);
}