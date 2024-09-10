jsvalue JsEngine::WrappedFromV8(Handle<Object> obj)
{
    jsvalue v;
       
	if (js_object_marshal_type == JSOBJECT_MARSHAL_TYPE_DYNAMIC) {
		v.type = JSVALUE_TYPE_WRAPPED;
		v.length = 0;
        // A Persistent<Object> is exactly the size of an IntPtr, right?
		// If not we're in deep deep trouble (on IA32 and AMD64 should be).
		// We should even cast it to void* because C++ doesn't allow to put
		// it in a union: going scary and scarier here.    
		v.value.ptr = new Persistent<Object>(Persistent<Object>::New(obj));
	} else {
		v.type = JSVALUE_TYPE_DICT;
		Local<Array> names = obj->GetOwnPropertyNames();
		v.length = names->Length();
		jsvalue* values = new jsvalue[v.length * 2];
		if (values != NULL) {
			for(int i = 0; i < v.length; i++) {
				int indx = (i * 2);
				Local<Value> key = names->Get(i);
				values[indx] = AnyFromV8(key);
				values[indx+1] = AnyFromV8(obj->Get(key));
			}
			v.value.arr = values;
		}
	}

	return v;
} 