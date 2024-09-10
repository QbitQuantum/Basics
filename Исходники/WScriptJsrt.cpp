JsValueRef WScriptJsrt::LoadScript(JsValueRef callee, LPCSTR fileName, LPCSTR fileContent, LPCSTR scriptInjectType, bool isSourceModule)
{
    HRESULT hr = E_FAIL;
    JsErrorCode errorCode = JsNoError;
    LPCWSTR errorMessage = _u("Internal error.");
    JsValueRef returnValue = JS_INVALID_REFERENCE;
    JsErrorCode innerErrorCode = JsNoError;
    JsContextRef currentContext = JS_INVALID_REFERENCE;
    JsRuntimeHandle runtime = JS_INVALID_RUNTIME_HANDLE;

    char fullPathNarrow[_MAX_PATH];
    size_t len = 0;

    IfJsrtErrorSetGo(ChakraRTInterface::JsGetCurrentContext(&currentContext));
    IfJsrtErrorSetGo(ChakraRTInterface::JsGetRuntime(currentContext, &runtime));

    if (fileName)
    {
        if (_fullpath(fullPathNarrow, fileName, _MAX_PATH) == nullptr)
        {
            IfFailGo(E_FAIL);
        }
        // canonicalize that path name to lower case for the profile storage
        // REVIEW: This doesn't work for UTF8...
        len = strlen(fullPathNarrow);
        for (size_t i = 0; i < len; i++)
        {
            fullPathNarrow[i] = (char)tolower(fullPathNarrow[i]);
        }
    }
    else
    {
        // No fileName provided (WScript.LoadScript()), use dummy "script.js"
        strcpy_s(fullPathNarrow, "script.js");
    }

    // this is called with LoadModuleCallback method as well where caller pass in a string that should be
    // treated as a module source text instead of opening a new file.
    if (isSourceModule || (strcmp(scriptInjectType, "module") == 0))
    {
        errorCode = LoadModuleFromString(fileName, fileContent);
    }
    else if (strcmp(scriptInjectType, "self") == 0)
    {
        JsContextRef calleeContext;
        IfJsrtErrorSetGo(ChakraRTInterface::JsGetContextOfObject(callee, &calleeContext));

        IfJsrtErrorSetGo(ChakraRTInterface::JsSetCurrentContext(calleeContext));

        errorCode = ChakraRTInterface::JsRunScriptUtf8(fileContent, GetNextSourceContext(), fullPathNarrow, &returnValue);

        if(errorCode == JsNoError)
        {
            errorCode = ChakraRTInterface::JsGetGlobalObject(&returnValue);
        }

        IfJsrtErrorSetGo(ChakraRTInterface::JsSetCurrentContext(currentContext));
    }
    else if (strcmp(scriptInjectType, "samethread") == 0)
    {
        JsValueRef newContext = JS_INVALID_REFERENCE;

        // Create a new context and set it as the current context
        IfJsrtErrorSetGo(ChakraRTInterface::JsCreateContext(runtime, &newContext));
        IfJsrtErrorSetGo(ChakraRTInterface::JsSetCurrentContext(newContext));

        // Initialize the host objects
        Initialize();

        errorCode = ChakraRTInterface::JsRunScriptUtf8(fileContent, GetNextSourceContext(), fullPathNarrow, &returnValue);

        if (errorCode == JsNoError)
        {
            errorCode = ChakraRTInterface::JsGetGlobalObject(&returnValue);
        }

        // Set the context back to the old one
        ChakraRTInterface::JsSetCurrentContext(currentContext);
    }
    else
    {
        errorCode = JsErrorInvalidArgument;
        errorMessage = _u("Unsupported argument type inject type.");
    }

Error:
    JsValueRef value = returnValue;
    if (errorCode != JsNoError)
    {
        if (innerErrorCode != JsNoError)
        {
            // Failed to retrieve the inner error message, so set a custom error string
            errorMessage = ConvertErrorCodeToMessage(errorCode);
        }

        JsValueRef error = JS_INVALID_REFERENCE;
        JsValueRef messageProperty = JS_INVALID_REFERENCE;

        ERROR_MESSAGE_TO_STRING(errCode, errorMessage, messageProperty);

        if (errCode == JsNoError)
        {
            errCode = ChakraRTInterface::JsCreateError(messageProperty, &error);
            if (errCode == JsNoError)
            {
                errCode = ChakraRTInterface::JsSetException(error);
            }
        }

        ChakraRTInterface::JsDoubleToNumber(errorCode, &value);
    }

    _flushall();

    return value;
}