void exit(int status)
#endif
{

		if (!__aborting)
	{
		__begin_critical_region(atexit_funcs_access);
		
		while (atexit_curr_func > 0)
			(*atexit_funcs[--atexit_curr_func])();
		
#if (__dest_os == __win32_os) && (STOP_PROGRAM_BEFORE_EXIT==1)

	if(GetFileType(GetStdHandle(STD_OUTPUT_HANDLE))==FILE_TYPE_CHAR)
{
	//printf("\n \n Press Enter to continue \n");
	//fflush(stdin);
	//getc(stdin);
}
#endif

		__end_critical_region(atexit_funcs_access);

	 /*
	 970218 bkoz
	 		need to move destroy global chain above __stdio_exit as
		 	some static objects may have destructors that flush streams
	 */
	 #if !__INTEL__
	 #if  __POWERPC__ || __CFM68K__ || (__MC68K__ && __A5__) || (__dest_os == __be_os)
		__destroy_global_chain();
	 #endif
	 #endif
		if (__stdio_exit)
		{
			(*__stdio_exit)();
			__stdio_exit = 0;
		}
	}

	__exit(status);
}