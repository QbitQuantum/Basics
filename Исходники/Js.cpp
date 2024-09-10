JsErrorCode CreateHostContext(JsRuntimeHandle runtime, int argc, wchar_t *argv [], int argumentsStart, JsContextRef *context)
{	
	JsCreateContext(runtime, context);
	
	JsSetCurrentContext(*context);

	
	JsValueRef hostObject;
	JsCreateObject(&hostObject);
	ghostObject = hostObject;

	JsValueRef globalObject;
	JsGetGlobalObject(&globalObject);
	
	JsPropertyIdRef hostPropertyId;
	JsGetPropertyIdFromName(L"app", &hostPropertyId); // app.XXXXX 

	JsSetProperty(globalObject, hostPropertyId, hostObject, true);

	//IfFailRet(DefineHostCallback(hostObject, L"msgbox", msgbox, nullptr));

	JsSetCurrentContext(JS_INVALID_REFERENCE);

	return JsNoError;
}