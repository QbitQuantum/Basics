void onProcessDestruction() throw ( ::jace::JNIException ) {

#ifdef SUPPORTS_PTHREADS
    int rc = pthread_key_delete( CLASSLOADER_KEY );
    if ( rc != 0 ) {
        std::string msg = "JNIHelper::setClassLoader()\n"
                "thread_key_delete() returned " + std::to_string( rc ) + ".";
        throw JNIException( msg );
    }
#elif _WIN32
    BOOL rc = TlsFree( CLASSLOADER_KEY );
    if ( !rc ) {
        std::string msg = "JNIHelper::setClassLoader()\n"
                "TlsFree() returned " + std::to_string( GetLastError() ) + ".";
        throw JNIException( msg );
    }
#endif
}