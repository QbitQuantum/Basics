void APIModule::log(const FunctionCallbackInfo<Value>& args)
{
	HandleScope scope(args.GetIsolate());
	if (args.Length()  == 1) {
		titanium::Utf8Value message(args[0]);
		APIModule::logInternal(LOG_LEVEL_INFO, LCAT, *message);
	} else {
		titanium::Utf8Value level(args[0]);
		titanium::Utf8Value message(APIModule::combineLogMessages(args, 1));

		if (strcasecmp(*level, "TRACE") == 0) {
			APIModule::logInternal(LOG_LEVEL_TRACE, LCAT, *message);
		} else if (strcasecmp(*level, "DEBUG") == 0) {
			APIModule::logInternal(LOG_LEVEL_DEBUG, LCAT, *message);
		} else if (strcasecmp(*level, "INFO") == 0) {
			APIModule::logInternal(LOG_LEVEL_INFO, LCAT, *message);
		} else if (strcasecmp(*level, "NOTICE") == 0) {
			APIModule::logInternal(LOG_LEVEL_NOTICE, LCAT, *message);
		} else if (strcasecmp(*level, "WARN") == 0) {
			APIModule::logInternal(LOG_LEVEL_WARN, LCAT, *message);
		} else if (strcasecmp(*level, "ERROR") == 0) {
			APIModule::logInternal(LOG_LEVEL_ERROR, LCAT, *message);
		} else if (strcasecmp(*level, "CRITICAL") == 0) {
			APIModule::logInternal(LOG_LEVEL_CRITICAL, LCAT, *message);
		} else if (strcasecmp(*level, "FATAL") == 0) {
			APIModule::logInternal(LOG_LEVEL_FATAL, LCAT, *message);
		} else {
			int size = strlen(*level) + strlen(*message) + 4;
			char *fmessage = new char[size];
			snprintf(fmessage, size, "[%s] %s", *level, *message);
			APIModule::logInternal(LOG_LEVEL_INFO, LCAT, fmessage);
			delete [] fmessage;
		}
	}
}