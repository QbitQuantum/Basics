/*
* For C-standard/POSIX/OS specific/Custom/JNI errors, this function is called. It sets a pointer which is checked
* by java method when native function returns. If the pointer is set exception of class as set by this function is
* thrown.
*
* The type 1 indicates standard (C-standard/POSIX) error, 2 indicate custom (defined by this library)
* error, 3 indicates custom error with message string, 4 indicates error number specific to Windows OS.
*/
void throw_serialcom_exception(JNIEnv *env, int type, int error_code, const char *msg) {

	DWORD ret = -1;
	errno_t err_code = 0;
	char buffer[256];
	jclass serialComExceptionClass = NULL;

	(*env)->ExceptionClear(env);
	serialComExceptionClass = (*env)->FindClass(env, SCOMEXPCLASS);
	if ((serialComExceptionClass == NULL) || ((*env)->ExceptionOccurred(env) != NULL)) {
		(*env)->ExceptionClear(env);
		LOGE(E_FINDCLASSSCOMEXPSTR, FAILTHOWEXP);
		return;
	}

	switch (type) {
	case 4:
		/* Caller has given Windows error code */
		memset(buffer, '\0', sizeof(buffer));
		ret = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error_code, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			(LPSTR)&buffer, sizeof(buffer), NULL);
		if (ret == 0) {
			LOGEN(FAILTHOWEXP, "FormatMessageA()", GetLastError());
		}
		ret = (*env)->ThrowNew(env, serialComExceptionClass, buffer);
		if (ret < 0) {
			LOGE(FAILTHOWEXP, buffer);
		}
		break;
	case 3:
		/* Caller has given exception message explicitly */
		ret = (*env)->ThrowNew(env, serialComExceptionClass, msg);
		if (ret < 0) {
			LOGE(FAILTHOWEXP, msg);
		}
		break;
	case 2:
		/* Caller has given custom error code, need to get exception message corresponding to this code. */
		switch (error_code) {
		default: _snprintf_s(buffer, 256, 256, "%s\0", E_UNKNOWN);
		}
		ret = (*env)->ThrowNew(env, serialComExceptionClass, buffer);
		if (ret < 0) {
			LOGE(FAILTHOWEXP, buffer);
		}
		break;
	case 1:
		/* Caller has given posix error code, get error message corresponding to this code. */
		return;
	case 5:
		/* Caller has given <errno.h> error code for windows, get error message corresponding to this code. */
		memset(buffer, '\0', sizeof(buffer));
		err_code = strerror_s(buffer, sizeof(buffer), error_code);
		if (err_code != 0) {
			LOGEN(FAILTHOWEXP, "strerror_s()", err_code);
		}
	}
}