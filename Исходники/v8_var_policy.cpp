 void V8BuilderPolicy::AppendToList(type const & var)
 {
   Nan::HandleScope scope;
   Local<Value> object(Nan::New(object_));
   assert(object->IsArray());
   Local<Array> arr = Local<Array>::Cast(object);
   arr->Set(arr->Length(), Nan::New(var));
 }