jobjectArray JNIV8Object::jniGetV8Keys(JNIEnv *env, jobject obj, jboolean ownOnly) {
    JNIV8Object_PrepareJNICall(JNIV8Object, Object, nullptr);

    MaybeLocal<Array> maybeArrayRef = ownOnly ? localRef->GetOwnPropertyNames(context) : localRef->GetPropertyNames();
    if(maybeArrayRef.IsEmpty()) {
        ptr->getEngine()->forwardV8ExceptionToJNI(&try_catch);
        return nullptr;
    }

    Local<Array> arrayRef = maybeArrayRef.ToLocalChecked();
    Local<Value> valueRef;

    jobjectArray result = nullptr;
    jstring string;

    std::string test;

    for(uint32_t i=0,n=arrayRef->Length(); i<n; i++) {
        MaybeLocal<Value> maybeValueRef = arrayRef->Get(context, i);
        if(!maybeValueRef.ToLocal<Value>(&valueRef)) {
            ptr->getEngine()->forwardV8ExceptionToJNI(&try_catch);
            return nullptr;
        }
        string = JNIV8Marshalling::v8string2jstring(valueRef->ToString(isolate));
        if(!result) {
            result = env->NewObjectArray(n, _jniString.clazz, string);
        } else {
            env->SetObjectArrayElement(result, i, string);
        }
        env->DeleteLocalRef(string);
    }

    return result;
}