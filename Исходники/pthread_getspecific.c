void *
pthread_getspecific(pthread_key_t key)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function returns the current value of key in the
 *      calling thread. If no value has been set for 'key' in
 *      the thread, NULL is returned.
 *
 * PARAMETERS
 *      key
 *              an instance of pthread_key_t
 *
 *
 * DESCRIPTION
 *      This function returns the current value of key in the
 *      calling thread. If no value has been set for 'key' in
 *      the thread, NULL is returned.
 *
 * RESULTS
 *              key value or NULL on failure
 *
 * ------------------------------------------------------
 */
{
	void * ptr;
	if (key == NULL)
		ptr = NULL;
	else {
		int lasterror = GetLastError();
		int lastWSAerror = WSAGetLastError();
		ptr = TlsGetValue(key->key);
		SetLastError(lasterror);
		WSASetLastError(lastWSAerror);
	}
	return ptr;
}