    void	xrDebug::_initialize		(const bool &dedicated)
    {
		handler							= 0;
        _set_new_mode					(1);					// gen exception if can't allocate memory
        _set_new_handler				(_out_of_memory	);		// exception-handler for 'out of memory' condition
		std::set_terminate				(_terminate);
		std::set_unexpected				(_terminate);
        ::SetUnhandledExceptionFilter	( UnhandledFilter );	// exception handler to all "unhandled" exceptions
    }