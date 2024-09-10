//
// Initialize handlers
//
INT_32 MainProcess::InitHandlers()
{
	// Load handlers
	oGlobalContext.error_log -> Info("Starting handlers");
	STLW::vector<HandlerConfig>::const_iterator itvHandlers = oGlobalContext.config.handlers.begin();
	while (itvHandlers != oGlobalContext.config.handlers.end())
	{
		const INT_32 iRC = LoadModule(itvHandlers -> type,
		                              itvHandlers -> name,
		                              itvHandlers -> library,
		                              itvHandlers -> driver,
		                              itvHandlers -> params,
		                              oGlobalContext.config.libexec_dirs,
		                              *oGlobalContext.error_log);
		if (iRC != 0) { return iRC; }

		oGlobalContext.error_log -> Info("Handler `%s` started", itvHandlers -> name.c_str());

		++itvHandlers;
	}

	// Initialize handlers
	itvHandlers = oGlobalContext.config.handlers.begin();
	while (itvHandlers != oGlobalContext.config.handlers.end())
	{
		// Initialize handler
		Handler * pHandler = static_cast<Handler *>(oGlobalContext.factory.GetObject(itvHandlers -> type + '/' + itvHandlers -> name));
		const INT_32 iRC = pHandler -> InitHandler(oGlobalContext, *itvHandlers, *oGlobalContext.error_log);
		if (iRC != 0) { return iRC; }

		oGlobalContext.error_log -> Info("Handler `%s` initialized", itvHandlers -> name.c_str());

		++itvHandlers;
	}
	oGlobalContext.error_log -> Info("All handlers started");

	oGlobalContext.error_log -> Info("Adding handlers to listeners");

	STLW::vector<ServiceConfig>::iterator itvServices = oGlobalContext.config.services.begin();
	while (itvServices != oGlobalContext.config.services.end())
	{
		// Get handler from factory
		Object * pObject = oGlobalContext.factory.GetObject("Handler/" + itvServices -> handler_name);
		if (pObject == NULL)
		{
			oGlobalContext.error_log -> Emerg("Can't find handler `%s`", itvServices -> handler_name.c_str());
			return -1;
		}
		itvServices -> handler = pObject;
		++itvServices;
	}
	oGlobalContext.error_log -> Info("Adding handlers to listeners finished");

return 0;
}