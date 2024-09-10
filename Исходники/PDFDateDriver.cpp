Handle<Value> PDFDateDriver::NewInstance(const Arguments& args)
{
    HandleScope scope;
    
    if(args.Length() != 1 || !args[0]->IsDate())
    {
		ThrowException(Exception::TypeError(String::New("Wrong arguments. Provide 1 argument which is a date")));
        return scope.Close(Undefined());
    }
    
    const unsigned argc = 1;
    Handle<Value> argv[argc] = {args[0]};
    Local<Object> instance = constructor->NewInstance(argc, argv);
    
    return scope.Close(instance);
}