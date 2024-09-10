	ThreadLocalStorage::~ThreadLocalStorage()
	{
		if (!instance)
			return;
#ifdef WIN32
		if (instance->cl_tls_index == TLS_OUT_OF_INDEXES)
			return;
		ThreadLocalStorage_Impl *tls_impl = (ThreadLocalStorage_Impl *)TlsGetValue(instance->cl_tls_index);
		if (tls_impl)
			tls_impl->release_reference();
#elif !defined(HAVE_TLS)
		if (!instance->cl_tls_index_created)
			return;
		ThreadLocalStorage_Impl *tls_impl = (ThreadLocalStorage_Impl *) pthread_getspecific(instance->cl_tls_index);
		if (tls_impl)
			tls_impl->release_reference();
#else
		if (instance->cl_tls_impl)
			instance->cl_tls_impl->release_reference();
#endif
	}