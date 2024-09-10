void CJSKadID::JSKadID(const v8::FunctionCallbackInfo<v8::Value> &args)
{
	v8::HandleScope HandleScope(v8::Isolate::GetCurrent());
	CUInt128 Value;
	if(args.Length() >= 1)
		Value = FromValue(args[0]);
	CJSScript* jScript = GetJSObject<CJSScript>(args.Holder());
	CJSObject* jObject = CJSVariant::New(new CKadIDObj(Value), jScript);
	args.GetReturnValue().Set(jObject->GetInstance());
}