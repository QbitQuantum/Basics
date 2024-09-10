//
// Log JIT method native load event to VTune 
//
void VTuneChakraProfile::LogMethodNativeLoadEvent(Js::FunctionBody* body, Js::FunctionEntryPointInfo* entryPoint)
{
#if ENABLE_NATIVE_CODEGEN
    if (isJitProfilingActive)
    {
        iJIT_Method_Load methodInfo;
        memset(&methodInfo, 0, sizeof(iJIT_Method_Load));
        const char16* methodName = body->GetExternalDisplayName();
        // Append function line number info to method name so that VTune can distinguish between polymorphic methods
        char16 methodNameBuffer[_MAX_PATH];
        ULONG lineNumber = body->GetLineNumber();
        char16 numberBuffer[20];
        _ltow_s(lineNumber, numberBuffer, 10);
        wcscpy_s(methodNameBuffer, methodName);
        if (entryPoint->GetJitMode() == ExecutionMode::SimpleJit)
        {
            wcscat_s(methodNameBuffer, _u(" Simple"));
        }
        wcscat_s(methodNameBuffer, _u(" {line:"));
        wcscat_s(methodNameBuffer, numberBuffer);
        wcscat_s(methodNameBuffer, _u("}"));

        size_t methodLength = wcslen(methodNameBuffer);
        Assert(methodLength < _MAX_PATH);
        size_t length = methodLength * 3 + 1;
        utf8char_t* utf8MethodName = HeapNewNoThrowArray(utf8char_t, length);
        if (utf8MethodName)
        {
            methodInfo.method_id = iJIT_GetNewMethodID();
            utf8::EncodeIntoAndNullTerminate(utf8MethodName, methodNameBuffer, (charcount_t)methodLength);
            methodInfo.method_name = (char*)utf8MethodName;
            methodInfo.method_load_address = (void*)entryPoint->GetNativeAddress();
            methodInfo.method_size = (uint)entryPoint->GetCodeSize();        // Size in memory - Must be exact

            LineNumberInfo numberInfo[1];

            uint lineCount = (entryPoint->GetNativeOffsetMapCount()) * 2 + 1; // may need to record both .begin and .end for all elements
            LineNumberInfo* pLineInfo = HeapNewNoThrowArray(LineNumberInfo, lineCount);

            if (pLineInfo == NULL || Js::Configuration::Global.flags.DisableVTuneSourceLineInfo)
            {
                // resort to original implementation, attribute all samples to first line
                numberInfo[0].LineNumber = lineNumber;
                numberInfo[0].Offset = 0;
                methodInfo.line_number_size = 1;
                methodInfo.line_number_table = numberInfo;
            }
            else
            {
                int size = entryPoint->PopulateLineInfo(pLineInfo, body);
                methodInfo.line_number_size = size;
                methodInfo.line_number_table = pLineInfo;
            }

            size_t urlLength = 0;
            utf8char_t* utf8Url = GetUrl(body, &urlLength);
            methodInfo.source_file_name = (char*)utf8Url;
            OUTPUT_TRACE(Js::ProfilerPhase, _u("Method load event: %s\n"), methodNameBuffer);
            iJIT_NotifyEvent(iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED, &methodInfo);

            HeapDeleteArray(lineCount, pLineInfo);

            if (urlLength > 0)
            {
                HeapDeleteArray(urlLength, utf8Url);
            }

            HeapDeleteArray(length, utf8MethodName);
        }
    }
#endif
}