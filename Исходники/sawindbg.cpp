static bool getWindbgInterfaces(JNIEnv* env, jobject obj) {
  // get windbg interfaces ..

  IDebugClient* ptrIDebugClient = 0;
  if (DebugCreate(__uuidof(IDebugClient), (PVOID*) &ptrIDebugClient) != S_OK) {
     THROW_NEW_DEBUGGER_EXCEPTION_("Windbg Error: not able to create IDebugClient object!", false);
  }
  env->SetLongField(obj, ptrIDebugClient_ID, (jlong) ptrIDebugClient);

  IDebugControl* ptrIDebugControl = 0;
  if (ptrIDebugClient->QueryInterface(__uuidof(IDebugControl), (PVOID*) &ptrIDebugControl)
     != S_OK) {
     THROW_NEW_DEBUGGER_EXCEPTION_("Windbg Error: not able to get IDebugControl", false);
  }
  env->SetLongField(obj, ptrIDebugControl_ID, (jlong) ptrIDebugControl);

  IDebugDataSpaces* ptrIDebugDataSpaces = 0;
  if (ptrIDebugClient->QueryInterface(__uuidof(IDebugDataSpaces), (PVOID*) &ptrIDebugDataSpaces)
     != S_OK) {
     THROW_NEW_DEBUGGER_EXCEPTION_("Windbg Error: not able to get IDebugDataSpaces object!", false);
  }
  env->SetLongField(obj, ptrIDebugDataSpaces_ID, (jlong) ptrIDebugDataSpaces);

  SAOutputCallbacks* ptrIDebugOutputCallbacks = new SAOutputCallbacks();
  ptrIDebugOutputCallbacks->AddRef();
  env->SetLongField(obj, ptrIDebugOutputCallbacks_ID, (jlong) ptrIDebugOutputCallbacks);
  CHECK_EXCEPTION_(false);

  IDebugAdvanced* ptrIDebugAdvanced = 0;
  if (ptrIDebugClient->QueryInterface(__uuidof(IDebugAdvanced), (PVOID*) &ptrIDebugAdvanced)
     != S_OK) {
     THROW_NEW_DEBUGGER_EXCEPTION_("Windbg Error: not able to get IDebugAdvanced object!", false);
  }
  env->SetLongField(obj, ptrIDebugAdvanced_ID, (jlong) ptrIDebugAdvanced);

  IDebugSymbols* ptrIDebugSymbols = 0;
  if (ptrIDebugClient->QueryInterface(__uuidof(IDebugSymbols), (PVOID*) &ptrIDebugSymbols)
     != S_OK) {
     THROW_NEW_DEBUGGER_EXCEPTION_("Windbg Error: not able to get IDebugSymbols object!", false);
  }
  env->SetLongField(obj, ptrIDebugSymbols_ID, (jlong) ptrIDebugSymbols);

  IDebugSystemObjects* ptrIDebugSystemObjects = 0;
  if (ptrIDebugClient->QueryInterface(__uuidof(IDebugSystemObjects), (PVOID*) &ptrIDebugSystemObjects)
     != S_OK) {
     THROW_NEW_DEBUGGER_EXCEPTION_("Windbg Error: not able to get IDebugSystemObjects object!", false);
  }
  env->SetLongField(obj, ptrIDebugSystemObjects_ID, (jlong) ptrIDebugSystemObjects);

  return true;
}