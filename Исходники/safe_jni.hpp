	method(JNIEnv *env, jclass cls, char const * const name, char const * const sig)
		: env_(env), mid_(NULL) {
		mid_ = getEnv()->GetStaticMethodID(cls, name, sig);
	}