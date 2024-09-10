EncodedJSValue JSC_HOST_CALL JSBlobConstructor::constructJSBlob(ExecState* exec)
{
    JSBlobConstructor* jsConstructor = jsCast<JSBlobConstructor*>(exec->callee());
    ScriptExecutionContext* context = jsConstructor->scriptExecutionContext();
    if (!context)
        return throwVMError(exec, createReferenceError(exec, "Blob constructor associated document is unavailable"));

    if (!exec->argumentCount()) {
        RefPtr<Blob> blob = Blob::create();
        return JSValue::encode(CREATE_DOM_WRAPPER(exec, jsConstructor->globalObject(), Blob, blob.get()));
    }

    JSValue firstArg = exec->argument(0);
    if (!isJSArray(firstArg))
        return throwVMError(exec, createTypeError(exec, "First argument of the constructor is not of type Array"));

    String type;
    String endings = "transparent";

    if (exec->argumentCount() > 1) {
        JSValue blobPropertyBagValue = exec->argument(1);

        if (!blobPropertyBagValue.isObject())
            return throwVMError(exec, createTypeError(exec, "Second argument of the constructor is not of type Object"));

        // Given the above test, this will always yield an object.
        JSObject* blobPropertyBagObject = blobPropertyBagValue.toObject(exec);

        // Create the dictionary wrapper from the initializer object.
        JSDictionary dictionary(exec, blobPropertyBagObject);

        // Attempt to get the endings property and validate it.
        bool containsEndings = dictionary.get("endings", endings);
        if (exec->hadException())
            return JSValue::encode(jsUndefined());

        if (containsEndings) {
            if (endings != "transparent" && endings != "native")
                return throwVMError(exec, createTypeError(exec, "The endings property must be either \"transparent\" or \"native\""));
        }

        // Attempt to get the type property.
        dictionary.get("type", type);
        if (exec->hadException())
            return JSValue::encode(jsUndefined());
    }

    ASSERT(endings == "transparent" || endings == "native");

    // FIXME: this would be better if the WebKitBlobBuilder were a stack object to avoid the allocation.
    RefPtr<WebKitBlobBuilder> blobBuilder = WebKitBlobBuilder::create();

    JSArray* array = asArray(firstArg);
    unsigned length = array->length();

    for (unsigned i = 0; i < length; ++i) {
        JSValue item = array->getIndex(i);
#if ENABLE(BLOB)
        if (item.inherits(&JSArrayBuffer::s_info))
            blobBuilder->append(toArrayBuffer(item));
        else
#endif
        if (item.inherits(&JSBlob::s_info))
            blobBuilder->append(toBlob(item));
        else {
            String string = ustringToString(item.toString(exec)->value(exec));
            if (exec->hadException())
                return JSValue::encode(jsUndefined());
            blobBuilder->append(string, endings, ASSERT_NO_EXCEPTION);
        }
    }

    RefPtr<Blob> blob = blobBuilder->getBlob(type);
    return JSValue::encode(CREATE_DOM_WRAPPER(exec, jsConstructor->globalObject(), Blob, blob.get()));
}