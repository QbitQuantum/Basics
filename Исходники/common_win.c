w_boolean_t w_remove_exception_handler(w_ptr_t handle)
{
	if (RemoveVectoredExceptionHandler(handle) == 0)
		return FALSE;

	return TRUE;
}