v8::Handle<v8::Value> CompoundShape_GetChildShape(const Arguments& args)
{
    HandleScope handle_scope;

    if ((args.Length() == 1) && args[0]->IsUint32())
    {
        CompoundShape* ptr = GetPtr(args.This());
        assert(ptr);

        unsigned int index = args[0]->ToUint32()->Value();
        if (index < ptr->getNbChildShapes())
            return handle_scope.Close(Uint32::New((unsigned int) ptr->getChildShape(index)));
    }

    return ThrowException(String::New("Invalid parameters, valid syntax:\ngetChildShape(childIndex)"));
}