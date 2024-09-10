int Conv::ToJavaMap(JNIEnv *jniEnv, Handle<Value> val, int componentType, jobject *jVal) {
  Local<Object> oVal;
  Local<Array> aPropertyNames;
  if(val.IsEmpty() || val->IsNull() || val->IsUndefined()) {
    *jVal = 0;
    return OK;
  }
  if(!val->IsObject())
    return ErrorType;
  
  oVal = val->ToObject();
  aPropertyNames = oVal->GetOwnPropertyNames();
  int len = aPropertyNames->Length();

  jobject ob = jniEnv->NewObject(mapClass, mapCtor);
  if(ob) {
    int res = OK;
    for(int i = 0; i < len; i++) {
      Local<String> key = Local<String>::Cast(aPropertyNames->Get(i));
      jstring jKey; jobject item;
      res = ToJavaString(jniEnv, key, &jKey);
      if(res != OK) break;
      res = ToJavaObject(jniEnv, oVal->Get(key), componentType, &item);
      if(res != OK) break;
      jniEnv->CallObjectMethod(ob, mapPut, jKey, item);
    }
  }
  if(ob) {
    *jVal = ob;
    return OK;
  }
  if(jniEnv->ExceptionCheck())
    jniEnv->ExceptionClear();
  return ErrorVM;
}