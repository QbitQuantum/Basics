P_LIB_API pboolean
p_dir_remove (const pchar	*path,
	      PError		**error)
{
	if (P_UNLIKELY (path == NULL)) {
		p_error_set_error_p (error,
				     (pint) P_ERROR_IO_INVALID_ARGUMENT,
				     0,
				     "Invalid input argument");
		return FALSE;
	}

	if (!p_dir_is_exists (path)) {
		p_error_set_error_p (error,
				     (pint) P_ERROR_IO_NOT_EXISTS,
				     0,
				     "Specified directory doesn't exist");
		return FALSE;
	}

	if (P_UNLIKELY (RemoveDirectoryA (path) == 0)) {
		p_error_set_error_p (error,
				     (pint) p_error_get_last_io (),
				     p_error_get_last_system (),
				     "Failed to call RemoveDirectoryA() to remove directory");
		return FALSE;
	} else
		return TRUE;
}