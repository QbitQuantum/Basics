	static inline void envTLSInit(void) {
		envTLS = TlsAlloc();
		if ( envTLS == TLS_OUT_OF_INDEXES )
			fprintf(stderr, "Failed to allocate TLS for JNIEnv.");
	}