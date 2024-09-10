/*
 * Class:     org_eclipse_cdt_utils_pty_PTY
 * Method:    waitFor
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_org_eclipse_cdt_utils_pty_PTY_waitFor
  (JNIEnv *env, jobject jobj, jint masterFD, jint pid)
{
	int status = -1;
    DWORD flags;

    int fd;
    std::map<int, winpty_t*> :: iterator fd2pty_Iter;
    std::map<int, int> :: iterator fd2rc_Iter;

    fd = masterFD;
    fd2pty_Iter = fd2pty.find(fd);
    if (fd2pty_Iter != fd2pty.end()) {
        winpty_t* winpty = fd2pty_Iter -> second;
    	if (winpty != NULL) {
            HANDLE handle = winpty_get_data_pipe(winpty);
            BOOL success;
	    	do {
                success = GetHandleInformation(handle, &flags);
                if (success) Sleep(500);
		    } while (success);

            fd2rc_Iter = fd2rc.find(fd);
            if (fd2rc_Iter != fd2rc.end()) {
                status = fd2rc_Iter -> second;
                fd2rc.erase(fd2rc_Iter);
            }
	    }
    }

	return status;
}