v8::Handle<v8::Value> CJavaFunction::Caller(const v8::Arguments& args) 
{
  CJavaFunction& func = *static_cast<CJavaFunction *>(v8::Handle<v8::External>::Cast(args.Data())->Value());

  jni::V8Env env(func.GetEnv());

  bool hasThiz = CManagedObject::IsWrapped(args.This()->ToObject());
  jobject thiz = hasThiz ? CManagedObject::Unwrap(args.This()->ToObject()).GetObject() : NULL;
  
  jobjectArray params = (jobjectArray) env.NewObjectArray(args.Length());

  for (size_t i=0; i<args.Length(); i++)
  {
    env->SetObjectArrayElement(params, i, env.Wrap(args[i]));
  }
  
  jobject method = func.GetMethod(args);
  static jmethodID mid = env.GetMethodID(env.buildins.java.lang.reflect.Method, "invoke", "(Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;");
  
  jobject result = env->CallObjectMethod(method, mid, thiz, params);

  return env.Close(env.Wrap(result));  
}