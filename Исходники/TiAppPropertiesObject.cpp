Handle<Value> TiAppPropertiesObject::_removeProperty(void* /*userContext*/, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 1)
    {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    if (!args[0]->IsString() && !args[0]->IsStringObject())
    {
        return ThrowException(String::New((string(Ti::Msg::Invalid_argument_expected_) + "String").c_str()));
    }

    QString key = QString::fromUtf8(*String::Utf8Value(args[0]));
    settings.remove(key);

    return Undefined();
}