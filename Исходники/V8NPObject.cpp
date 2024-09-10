// FIXME: need comments.
// Params: holder could be HTMLEmbedElement or NPObject
static void npObjectInvokeImpl(const v8::FunctionCallbackInfo<v8::Value>& args, InvokeFunctionType functionId)
{
    NPObject* npObject;

    WrapperWorldType currentWorldType = worldType(args.GetIsolate());
    // These three types are subtypes of HTMLPlugInElement.
    if (V8HTMLAppletElement::HasInstance(args.Holder(), args.GetIsolate(), currentWorldType) || V8HTMLEmbedElement::HasInstance(args.Holder(), args.GetIsolate(), currentWorldType)
        || V8HTMLObjectElement::HasInstance(args.Holder(), args.GetIsolate(), currentWorldType)) {
        // The holder object is a subtype of HTMLPlugInElement.
        HTMLPlugInElement* element;
        if (V8HTMLAppletElement::HasInstance(args.Holder(), args.GetIsolate(), currentWorldType))
            element = V8HTMLAppletElement::toNative(args.Holder());
        else if (V8HTMLEmbedElement::HasInstance(args.Holder(), args.GetIsolate(), currentWorldType))
            element = V8HTMLEmbedElement::toNative(args.Holder());
        else
            element = V8HTMLObjectElement::toNative(args.Holder());
        ScriptInstance scriptInstance = element->getInstance();
        if (scriptInstance) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::HandleScope handleScope(isolate);
            npObject = v8ObjectToNPObject(scriptInstance->newLocal(isolate));
        } else
            npObject = 0;
    } else {
        // The holder object is not a subtype of HTMLPlugInElement, it must be an NPObject which has three
        // internal fields.
        if (args.Holder()->InternalFieldCount() != npObjectInternalFieldCount) {
            throwError(v8ReferenceError, "NPMethod called on non-NPObject", args.GetIsolate());
            return;
        }

        npObject = v8ObjectToNPObject(args.Holder());
    }

    // Verify that our wrapper wasn't using a NPObject which has already been deleted.
    if (!npObject || !_NPN_IsAlive(npObject)) {
        throwError(v8ReferenceError, "NPObject deleted", args.GetIsolate());
        return;
    }

    // Wrap up parameters.
    int numArgs = args.Length();
    OwnArrayPtr<NPVariant> npArgs = adoptArrayPtr(new NPVariant[numArgs]);

    for (int i = 0; i < numArgs; i++)
        convertV8ObjectToNPVariant(args[i], npObject, &npArgs[i]);

    NPVariant result;
    VOID_TO_NPVARIANT(result);

    bool retval = true;
    switch (functionId) {
    case InvokeMethod:
        if (npObject->_class->invoke) {
            v8::Handle<v8::String> functionName = v8::Handle<v8::String>::Cast(args.Data());
            NPIdentifier identifier = getStringIdentifier(functionName);
            retval = npObject->_class->invoke(npObject, identifier, npArgs.get(), numArgs, &result);
        }
        break;
    case InvokeConstruct:
        if (npObject->_class->construct)
            retval = npObject->_class->construct(npObject, npArgs.get(), numArgs, &result);
        break;
    case InvokeDefault:
        if (npObject->_class->invokeDefault)
            retval = npObject->_class->invokeDefault(npObject, npArgs.get(), numArgs, &result);
        break;
    default:
        break;
    }

    if (!retval)
        throwError(v8GeneralError, "Error calling method on NPObject.", args.GetIsolate());

    for (int i = 0; i < numArgs; i++)
        _NPN_ReleaseVariantValue(&npArgs[i]);

    // Unwrap return values.
    v8::Handle<v8::Value> returnValue;
    if (_NPN_IsAlive(npObject))
        returnValue = convertNPVariantToV8Object(&result, npObject, args.GetIsolate());
    _NPN_ReleaseVariantValue(&result);

    v8SetReturnValue(args, returnValue);
}