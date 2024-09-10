void Ti::TiProxy::initWithObject(Handle<Object> obj)
{
	HandleScope scope;
	Local<Array> props = obj->GetPropertyNames();
	for(int i = 0, len = props->Length(); i < len; i++) {
		Local<String> key = props->Get(i)->ToString();
		Local<Value> val = obj->Get(key);
		_jsObject->Set(key, val);
	}
}