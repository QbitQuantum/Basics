METHOD_RETURN_TYPE InputFileDriver::New(const ARGS_TYPE& args)
{
    CREATE_ISOLATE_CONTEXT;
	CREATE_ESCAPABLE_SCOPE;
    EXPOSE_EXTERNAL_ARGS(ConstructorsHolder, externalHolder)
    
    InputFileDriver* inputFile = new InputFileDriver();

    inputFile->holder = externalHolder;
    
    if(args.Length() == 1 && args[0]->IsString())
        inputFile->OpenFile(*UTF_8_VALUE(args[0]->TO_STRING()));
    
    inputFile->Wrap(args.This());
	SET_FUNCTION_RETURN_VALUE(args.This())
}