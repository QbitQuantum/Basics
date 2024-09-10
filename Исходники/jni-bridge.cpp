// called by PluginAppletViewer.java nativeInvokeNative()
static jboolean invokeNative(JNIEnv* jniEnv,
                             jobject thiz,            // TODO ???
                             jint jnpp,               // root npp instance given to jni-bridge::surfaceCreated() -> handed over to DexLoader.loadDexInit()
                             jint jsobj_addr,         // via JsObject from pluginAppletViewer.getWindow();
                             jstring jmethodName,     // may be null
                             jobject args[])
{
  NPP npp = (NPP)jnpp;
  if(npp)
  {
    if(jniEnv && browser && browser->pluginthreadasynccall)
    {
      InvokeNativeObject* invokeNativeObject = (InvokeNativeObject*)malloc(sizeof(InvokeNativeObject));
      if(invokeNativeObject)
      {
        const char* methodName = NULL;
        if(jmethodName)
          methodName = jniEnv->GetStringUTFChars(jmethodName, NULL);

//        if(methodName)
//          gLogI.log(npp, kDebug_ANPLogType, "jni-bridge invokeNative() npp=%p jsobj_addr=%p methodname=%s ...",npp,jsobj_addr,methodName);
//        else
//          gLogI.log(npp, kDebug_ANPLogType, "jni-bridge invokeNative() npp=%p jsobj_addr=%p ...",npp,jsobj_addr);

        bzero(invokeNativeObject, sizeof(InvokeNativeObject));
        invokeNativeObject->npp = npp;
        invokeNativeObject->jsobj = (NPObject*)jsobj_addr;
        if(methodName)
          strcpy(invokeNativeObject->methodName,methodName);
        //invokeNativeObject->args = args;    // todo

        //gLogI.log(npp, kDebug_ANPLogType, "jni-bridge invokeNative() npp=%p jsobj=%p use pluginthreadasynccall()...",npp,invokeNativeObject->jsobj);
        browser->pluginthreadasynccall(npp, &invokeNativeAsync, (void*)invokeNativeObject);
        // invokeNativeObject may now be freed
        //gLogI.log(npp, kDebug_ANPLogType, "jni-bridge invokeNative() called ... ");

        if(jmethodName)
          jniEnv->ReleaseStringUTFChars(jmethodName, methodName);
        //gLogI.log(npp, kDebug_ANPLogType, "jni-bridge invokeNative() done");
        return true;
      }
    }

    gLogI.log(npp, kDebug_ANPLogType, "jni-bridge invokeNative() done fail");
  }
  return false;
}