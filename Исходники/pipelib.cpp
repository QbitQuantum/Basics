PIPELIB_API int proc_wait_for(int handle) {
	int err_code;
	_cwait(&err_code, handle, NULL);
	return err_code;
}