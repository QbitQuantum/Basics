Handle<Value> WrappedScript::CreateContext(const Arguments& args)
{
	HandleScope scope;

	Persistent<Context> context = Context::New(NULL, WrappedContext::global_template);
	WrappedContext *wrappedContext = new WrappedContext(context);
	Local<Object> global = context->Global();

	// Allow current context access to newly created context's objects.
	context->SetSecurityToken(Context::GetCurrent()->GetSecurityToken());

	// If a sandbox is provided initial the new context's global with it.
	if (args.Length() > 0) {
		Local<Object> sandbox = args[0]->ToObject();
		Local<Array> keys = sandbox->GetPropertyNames();

		for (uint32_t i = 0; i < keys->Length(); i++) {
			Handle<String> key = keys->Get(Integer::New(i))->ToString();
			Handle<Value> value = sandbox->Get(key);
			if (value == sandbox) {
				value = global;
			}
			global->Set(key, value);
		}
	}

	return scope.Close(global);
}