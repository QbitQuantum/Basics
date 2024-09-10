void CALLBACK callback(MethodID methodID, int callID, wstring& address, Cause cause, wstring* callInfo) {
    static HANDLE hMutex = CreateMutex(NULL, FALSE, "callbackMutex");
    DWORD dwWaitResult = WaitForSingleObject(hMutex, 5000L);
	logger->debug("Entering callback method %d: callID=%d, address=%S...", methodID, callID, address.c_str());
    if(dwWaitResult == WAIT_OBJECT_0) {
	    try{
		    JNIEnv *localEnv = NULL;
		    g_javaVM->AttachCurrentThread((void**)&localEnv, NULL);
		    jclass cls = localEnv->GetObjectClass(g_thisObj);

            jmethodID callbackID = NULL;
			for (int retry = 0; callbackID == NULL && retry < 5; retry++) {
				callbackID = localEnv->GetMethodID(cls, "callback", "(IILjava/lang/String;I[Ljava/lang/String;)V");
				// if we have to try again, delay for 250 ms
				if (callbackID == NULL && retry < 5) {
					Sleep(250);
				}
				logger->debug("callback methodID: %p, retry=%d", callbackID, retry);
			}

		    if (callbackID == NULL) {
			    logger->fatal("Callback method not available.");
		    } else {
			    jint jMethodID = methodID;
			    jint jCallID = callID;
			    jstring jAddress = localEnv->NewString(((jchar *)address.c_str()), (jsize)address.length());
			    jint jCause = cause;

			    jobjectArray objCallInfo = NULL;
			    if(callInfo != NULL) {
				    logger->debug("Setting callInfo...");
				    jclass oCls = localEnv->FindClass("java/lang/String");
				    objCallInfo = localEnv->NewObjectArray(4, oCls, NULL);
				    for (int i=0; i<4; i++) {
					    jstring jInfo = localEnv->NewString(((jchar *)callInfo[i].c_str()), (jsize)callInfo[i].length());
					    localEnv->SetObjectArrayElement(objCallInfo, i, jInfo);
				    }
			    } else {
				    logger->debug("No callInfo for this callback.");
			    }
			    localEnv->CallVoidMethod(g_thisObj, callbackID, jMethodID, jCallID, jAddress, jCause, objCallInfo);
				g_javaVM->DetachCurrentThread();
			    logger->debug("Java callback successfully called.");
		    }
	    } catch(...){
		    logger->fatal("Callback failed.");
		}
        ReleaseMutex(hMutex);
    } else {
		logger->fatal("Cannot obtain callback mutex: dwWaitResult=%08X.", dwWaitResult);
    }
}