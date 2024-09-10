ofxOscReceiver::ofxOscReceiver()
{
#ifdef TARGET_WIN32
	mutex = CreateMutexA( NULL, FALSE, NULL );
#else
	pthread_mutex_init( &mutex, NULL );
#endif
}