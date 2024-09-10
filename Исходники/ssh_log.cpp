	static void ssh_set_exceptionHandlers()
	{
		// установить фильтр исключений
		SetUnhandledExceptionFilter(Win32UnhandledExceptionFilter);
		// установить режимы отчета библиотеки времени выполнения
		//_CrtSetReportMode(_CRT_ERROR, 0);
		_CrtSetReportMode(_CRT_ASSERT, 0);

		set_terminate(ssh_terminate_handler);
		set_unexpected(ssh_unexp_handler);
		_set_purecall_handler(ssh_purecall_handler);
		_set_invalid_parameter_handler(ssh_invalid_parameter_handler);
		_set_new_handler(ssh_new_handler);
//		_set_security_error_handler(ssh_security_handler);
		signal(SIGABRT, ssh_signal_handler);
		signal(SIGINT, ssh_signal_handler);
		signal(SIGTERM, ssh_signal_handler);
		signal(SIGFPE, ssh_signal_handler);
		signal(SIGILL, ssh_signal_handler);
		signal(SIGSEGV, ssh_signal_handler);
	}