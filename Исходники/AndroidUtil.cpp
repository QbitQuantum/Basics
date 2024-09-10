void AndroidUtil::throwRuntimeException(const std::string &message) {
	getEnv()->ThrowNew(Class_java_lang_RuntimeException.j(), message.c_str());
}