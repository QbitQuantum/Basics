JNIEXPORT jlong JNICALL Java_com4j_Native_createInstance(
	JNIEnv* env, jclass __unused__, jstring _progId, jint clsctx, jlong iid1, jlong iid2 ) {
	
	MyGUID iid(iid1,iid2);
	CLSID clsid;
	HRESULT hr;
	JString progId(env,_progId);

	hr = CLSIDFromProgID(progId,&clsid);
	if(FAILED(hr)) {
		if(FAILED(CLSIDFromString( const_cast<LPOLESTR>(LPCOLESTR(progId)),&clsid))) {
			error(env,__FILE__,__LINE__,hr,"Unrecognized CLSID");
			return 0;
		}
	}

	void* p;

	if(clsctx&(CLSCTX_LOCAL_SERVER|CLSCTX_REMOTE_SERVER)) {
		IUnknown* pUnk = NULL;
		hr = CoCreateInstance(clsid,NULL,clsctx,__uuidof(IUnknown),(void**)&pUnk);
		if(FAILED(hr)) {
			error(env,__FILE__,__LINE__,hr,"CoCreateInstance failed");
			return 0;
		}
		hr = OleRun(pUnk);
		if(FAILED(hr)) {
			pUnk->Release();
			error(env,__FILE__,__LINE__,hr,"OleRun failed");
			return 0;
		}
		hr = pUnk->QueryInterface(iid,&p);
		pUnk->Release();

		if(FAILED(hr)) {
			error(env,__FILE__,__LINE__,hr,"QueryInterface failed");
			return 0;
		}

	} else {
		// just the plain CoCreateInstance
		hr = CoCreateInstance(clsid,NULL,clsctx,iid,&p);
		if(FAILED(hr)) {
			error(env,__FILE__,__LINE__,hr,"CoCreateInstance failed");
			return 0;
		}
	}
	return reinterpret_cast<jlong>(p);
}