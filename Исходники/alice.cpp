static void alice_output(bool error, const SCHAR* format, ...)
{

	AliceGlobals* tdgbl = AliceGlobals::getSpecific();

	va_list arglist;
	va_start(arglist, format);
	Firebird::string buf;
	buf.vprintf(format, arglist);
	va_end(arglist);

	if (error)
		tdgbl->uSvc->outputError(buf.c_str());
	else
		tdgbl->uSvc->outputVerbose(buf.c_str());
}