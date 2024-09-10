void c_to_factor_toplevel(CELL quot)
{
	if(!AddVectoredExceptionHandler(0, (void*)exception_handler))
		fatal_error("AddVectoredExceptionHandler failed", 0);
	c_to_factor(quot);
	RemoveVectoredExceptionHandler((void*)exception_handler);
}