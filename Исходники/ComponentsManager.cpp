Handle<Value> ComponentsManager_Create(const Arguments& args)
{
    HandleScope handle_scope;

    ComponentsManager* ptr = GetPtr(args.This());
    assert(ptr);

    if ((args.Length() == 3) && args[0]->IsString() && args[1]->IsString() && args[2]->IsObject())
    {
        return handle_scope.Close(toJavaScript(ptr->create(*String::AsciiValue(args[0]->ToString()),
                                                           *String::AsciiValue(args[1]->ToString()),
                                                           fromJSComponentsList(args[2]))));
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\ncreate(type, name, components_list)"));
}