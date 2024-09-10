/**
 * Used for user supplied input/output functions.  See initDxClass();
 */
long dx_uio_seek (int fd, long offset, int whence) {

	JavaVM *vm = jvr_getVM();
	JNIEnv *e;
	int detach = 0;
	if (vm->GetEnv((void **)&e, JNI_VERSION_1_2) != JNI_OK) {
		vm->AttachCurrentThread((void**)&e,&attachArgs);
		detach = 1;
	}
	if (e->ExceptionOccurred()) {
		e->ExceptionDescribe();
		e->ExceptionClear();
		return -1;
	}
	long ret = e->CallStaticLongMethod(dx_class,dx_uio_seek_method,(jint) fd,(jlong) offset,(jint) whence);
	if (detach) { vm->DetachCurrentThread(); }
	return ret;

}