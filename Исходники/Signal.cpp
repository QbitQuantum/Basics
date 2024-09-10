Handle<Value> Signal_Fire(const Arguments& args)
{
    HandleScope handle_scope;

    Signal* self = GetPtr(args.This());
    assert(self);

    Variant* pValue = 0;

    if (args.Length() == 1)
        pValue = fromJSVariant(args[0]);

    self->fire(pValue);

    return Handle<Value>();
}