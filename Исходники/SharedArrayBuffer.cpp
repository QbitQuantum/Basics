    // SharedArrayBuffer.prototype.slice
    Var SharedArrayBuffer::EntrySlice(RecyclableObject* function, CallInfo callInfo, ...)
    {
        PROBE_STACK(function->GetScriptContext(), Js::Constants::MinStackDefault);

        ARGUMENTS(args, callInfo);
        ScriptContext* scriptContext = function->GetScriptContext();

        AssertMsg(args.Info.Count > 0, "Should always have implicit 'this'");

        Assert(!(callInfo.Flags & CallFlags_New));

        if (!SharedArrayBuffer::Is(args[0]))
        {
            JavascriptError::ThrowTypeError(scriptContext, JSERR_NeedSharedArrayBufferObject);
        }

        JavascriptLibrary* library = scriptContext->GetLibrary();
        SharedArrayBuffer* currentBuffer = SharedArrayBuffer::FromVar(args[0]);

        int64 currentLen = (int64)currentBuffer->GetByteLength();
        int64 start = 0, end = 0;
        int64 newLen = 0;

        // If no start or end arguments, use the entire length
        if (args.Info.Count < 2)
        {
            newLen = currentLen;
        }
        else
        {
            start = JavascriptArray::GetIndexFromVar(args[1], currentLen, scriptContext);

            // If no end argument, use length as the end
            if (args.Info.Count < 3 || args[2] == library->GetUndefined())
            {
                end = currentLen;
            }
            else
            {
                end = JavascriptArray::GetIndexFromVar(args[2], currentLen, scriptContext);
            }

            newLen = end > start ? end - start : 0;
        }

        // We can't have allocated an SharedArrayBuffer with byteLength > MaxArrayBufferLength.
        // start and end are clamped to valid indices, so the new length also cannot exceed MaxArrayBufferLength.
        // Therefore, should be safe to cast down newLen to uint32.
        Assert(newLen < MaxSharedArrayBufferLength);
        uint32 newbyteLength = static_cast<uint32>(newLen);

        SharedArrayBuffer* newBuffer = nullptr;

        if (scriptContext->GetConfig()->IsES6SpeciesEnabled())
        {
            JavascriptFunction* defaultConstructor = scriptContext->GetLibrary()->GetSharedArrayBufferConstructor();
            RecyclableObject* constructor = JavascriptOperators::SpeciesConstructor(currentBuffer, defaultConstructor, scriptContext);
            AssertOrFailFast(JavascriptOperators::IsConstructor(constructor));

            bool isDefaultConstructor = constructor == defaultConstructor;
            Js::Var newVar = JavascriptOperators::NewObjectCreationHelper_ReentrancySafe(constructor, isDefaultConstructor, scriptContext->GetThreadContext(), [=]()->Js::Var
            {
                Js::Var constructorArgs[] = { constructor, JavascriptNumber::ToVar(newbyteLength, scriptContext) };
                Js::CallInfo constructorCallInfo(Js::CallFlags_New, _countof(constructorArgs));
                return JavascriptOperators::NewScObject(constructor, Js::Arguments(constructorCallInfo, constructorArgs), scriptContext);
            });

            if (!SharedArrayBuffer::Is(newVar))
            {
                JavascriptError::ThrowTypeError(scriptContext, JSERR_NeedSharedArrayBufferObject);
            }

            newBuffer = SharedArrayBuffer::FromVar(newVar);

            if (newBuffer == currentBuffer)
            {
                JavascriptError::ThrowTypeError(scriptContext, JSERR_NeedSharedArrayBufferObject);
            }

            if (newBuffer->GetByteLength() < newbyteLength)
            {
                JavascriptError::ThrowTypeError(scriptContext, JSERR_ArgumentOutOfRange, _u("SharedArrayBuffer.prototype.slice"));
            }
        }
        else
        {
            newBuffer = library->CreateSharedArrayBuffer(newbyteLength);
        }

        Assert(newBuffer);
        Assert(newBuffer->GetByteLength() >= newbyteLength);

        // Don't bother doing memcpy if we aren't copying any elements
        if (newbyteLength > 0)
        {
            AssertMsg(currentBuffer->GetBuffer() != nullptr, "buffer must not be null when we copy from it");

            js_memcpy_s(newBuffer->GetBuffer(), newbyteLength, currentBuffer->GetBuffer() + start, newbyteLength);
        }

        return newBuffer;
    }