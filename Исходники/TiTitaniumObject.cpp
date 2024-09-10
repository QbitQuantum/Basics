Handle<Value> TiTitaniumObject::_createBuffer(void* userContext, TiObject*, const Arguments& args)
{
    HandleScope handleScope;
    TiTitaniumObject* obj = (TiTitaniumObject*) userContext;
    Handle<ObjectTemplate> global = getObjectTemplateFromJsObject(args.Holder());
    Handle<Object> result = global->NewInstance();
    TiBufferObject* newBuffer = TiBufferObject::createBuffer(obj->objectFactory_);
    newBuffer->setValue(result);
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        Local<Object> settingsObj = Local<Object>::Cast(args[0]);
        newBuffer->setParametersFromObject(newBuffer, settingsObj);
    }
    setTiObjectToJsObject(result, newBuffer);
    return handleScope.Close(result);
}