JNIEXPORT jobject JNICALL Java_org_racob_com_DispatchProxy_MarshalFromStream
  (JNIEnv *env, jobject _this, jint pointer)
{
  IStream *ps = (IStream *) pointer;
  if (!ps) {
    ThrowComFail(env, "Could not get IStream from DispatchProxy", -1);
    return NULL;
  }
  
  IDispatch *pD;
  HRESULT hr = CoGetInterfaceAndReleaseStream(ps, IID_IDispatch, (void **)&pD);

  if (!SUCCEEDED(hr)) {
    ThrowComFail(env, "Could not Marshal Dispatch from IStream", hr);
    return NULL;
  }
  jclass autoClass = env->FindClass("org/racob/com/Dispatch");
  jmethodID autoCons = env->GetMethodID(autoClass, "<init>", "(I)V");
  // construct a Dispatch object to return
  // I am copying the pointer to java
  if (pD) pD->AddRef();
  jobject newAuto = env->NewObject(autoClass, autoCons, pD);
  return newAuto;
}