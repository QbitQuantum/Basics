Js::Var WabtInterface::EntryConvertWast2Wasm(RecyclableObject* function, CallInfo callInfo, ...)
{
    ScriptContext* scriptContext = function->GetScriptContext();
    PROBE_STACK(function->GetScriptContext(), Constants::MinStackDefault);

    ARGUMENTS(args, callInfo);
    AssertMsg(args.Info.Count > 0, "Should always have implicit 'this'");

    Assert(!(callInfo.Flags & CallFlags_New));

    if (args.Info.Count < 2 || !JavascriptString::Is(args[1]))
    {
        JavascriptError::ThrowTypeError(scriptContext, WASMERR_NeedBufferSource);
    }
    bool isSpecText = false;
    if (args.Info.Count > 2)
    {
        // optional config object
        if (!JavascriptOperators::IsObject(args[2]))
        {
            JavascriptError::ThrowTypeError(scriptContext, JSERR_NeedObject, _u("config"));
        }
        DynamicObject * configObject = JavascriptObject::FromVar(args[2]);

        Js::Var isSpecVar = JavascriptOperators::OP_GetProperty(configObject, PropertyIds::spec, scriptContext);
        isSpecText = JavascriptConversion::ToBool(isSpecVar, scriptContext);
    }

    ArenaAllocator arena(_u("Wast2Wasm"), scriptContext->GetThreadContext()->GetPageAllocator(), Throw::OutOfMemory);
    Context context;
    size_t wastSize;
    char* wastBuffer = nullptr;

    ENTER_PINNED_SCOPE(JavascriptString, string);
    string = (JavascriptString*)args[1];
    const char16* str = string->GetString();
    context.allocator = &arena;
    context.scriptContext = scriptContext;

    size_t origSize = string->GetLength();
    auto allocator = [&arena](size_t size) {return (utf8char_t*)AnewArray(&arena, byte, size);};
    utf8::WideStringToNarrow(allocator, str, origSize, &wastBuffer, &wastSize);
    LEAVE_PINNED_SCOPE();   //  string

    try
    {
        ChakraWabt::SpecContext spec;
        ChakraWabt::ChakraContext wabtCtx;
        wabtCtx.user_data = &context;
        wabtCtx.createBuffer = CreateBuffer;
        wabtCtx.features.sign_extends = CONFIG_FLAG(WasmSignExtends);
        if (isSpecText)
        {
            wabtCtx.spec = &spec;
            spec.setProperty = SetProperty;
            spec.int32ToVar = Int32ToVar;
            spec.int64ToVar = Int64ToVar;
            spec.stringToVar = StringToVar;
            spec.createObject = CreateObject;
            spec.createArray = CreateArray;
            spec.push = Push;
        }
        void* result = ChakraWabt::ConvertWast2Wasm(wabtCtx, wastBuffer, (uint)wastSize, isSpecText);
        if (result == nullptr)
        {
            return scriptContext->GetLibrary()->GetUndefined();
        }
        return result;
    }
    catch (ChakraWabt::Error& e)
    {
        JavascriptError::ThrowTypeErrorVar(scriptContext, WABTERR_WabtError, NarrowStringToWide(&context, e.message));
    }
}