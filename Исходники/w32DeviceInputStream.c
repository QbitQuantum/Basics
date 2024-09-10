/*
 * Function:   w32DeviceInputStream_getReadCountNC
 * Purpose:    Check serial port device event 
 * Signature: ()I
 * Return:     0 - Fail
 *			   none zero - succeeds	
 */
int w32DeviceInputStream_getReadCountNC(JNIEnv *jenv, jobject jobj)
{
    DWORD	dwCommEvent = 0;
	HANDLE  osHandle;
	
	jclass		jc;
	jclass		ec;
	jfieldID	jf;
	jint 		fd = -1;
	int			dc = 0;
	// Get the exception class.
	ec = (*jenv)->FindClass(jenv, "java/io/IOException");
	assert(ec);
	// Get the file descriptor.
	jc = (*jenv)->GetObjectClass(jenv, jobj);
	assertexc(jc);
	jf = (*jenv)->GetFieldID(jenv, jc, "fd", "I");
	assertexc(jf);
	fd = (*jenv)->GetIntField(jenv, jobj, jf);
	if (fd == -1) {
		(*jenv)->ThrowNew(jenv, ec, "");
	}
	osHandle = (HANDLE)fd;
	if(!GetCommMask( osHandle, &dwCommEvent ))
		return GetLastError();
	
	dwCommEvent |= EV_RXCHAR;
	if( !SetCommMask( osHandle, dwCommEvent ))
		return GetLastError();
	if( !WaitCommEvent( osHandle, &dwCommEvent, NULL ))
		return GetLastError();
	return (dwCommEvent&EV_RXCHAR);
}  /* w32DeviceInputStream_getReadCountNC() */