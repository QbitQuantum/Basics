    void* AsmJsEncoder::Encode( FunctionBody* functionBody )
    {
        Assert( functionBody );
        mFunctionBody = functionBody;
#if DBG_DUMP
        AsmJsJitTemplate::Globals::CurrentEncodingFunction = mFunctionBody;
#endif
        AsmJsFunctionInfo* asmInfo = functionBody->GetAsmJsFunctionInfo();
        FunctionEntryPointInfo* entryPointInfo = ((FunctionEntryPointInfo*)(functionBody->GetDefaultEntryPointInfo()));
        // number of var on the stack + ebp + eip
        mIntOffset = asmInfo->GetIntByteOffset() + GetOffset<Var>();
        mDoubleOffset = asmInfo->GetDoubleByteOffset() + GetOffset<Var>();
        mFloatOffset = asmInfo->GetFloatByteOffset() + GetOffset<Var>();
        mSimdOffset = asmInfo->GetSimdByteOffset() + GetOffset<Var>();

        NoRecoverMemoryArenaAllocator localAlloc(_u("BE-AsmJsEncoder"), GetPageAllocator(), Js::Throw::OutOfMemory);
        mLocalAlloc = &localAlloc;

        mRelocLabelMap = Anew( mLocalAlloc, RelocLabelMap, mLocalAlloc );
        mTemplateData = AsmJsJitTemplate::InitTemplateData();
        mEncodeBufferSize = GetEncodeBufferSize(functionBody);
        mEncodeBuffer = AnewArray((&localAlloc), BYTE, mEncodeBufferSize);
        mPc = mEncodeBuffer;
        mReader.Create( functionBody );
        ip = mReader.GetIP();

#ifdef ENABLE_DEBUG_CONFIG_OPTIONS
        if( PHASE_TRACE( Js::AsmjsEncoderPhase, mFunctionBody ) )
        {
            Output::Print( _u("\n\n") );
            functionBody->DumpFullFunctionName();
            Output::Print( _u("\n StackSize = %d , Offsets: Var = %d, Int = %d, Double = %d\n"), mFunctionBody->GetAsmJsFunctionInfo()->GetTotalSizeinBytes(), GetOffset<Var>(), GetOffset<int>(), GetOffset<double>() );
        }
#endif

        AsmJsJitTemplate::FunctionEntry::ApplyTemplate( this, mPc );
        while( ReadOp() ){}
        AsmJsJitTemplate::FunctionExit::ApplyTemplate( this, mPc );

        AsmJsJitTemplate::FreeTemplateData( mTemplateData );
#if DBG_DUMP
        AsmJsJitTemplate::Globals::CurrentEncodingFunction = nullptr;
#endif
        ApplyRelocs();

        ptrdiff_t codeSize = mPc - mEncodeBuffer;
        if( codeSize > 0 )
        {
            Assert( ::Math::FitsInDWord( codeSize ) );

            BYTE *buffer;
            EmitBufferAllocation *allocation = GetCodeGenAllocator()->emitBufferManager.AllocateBuffer( codeSize, &buffer, 0, 0 );
            functionBody->GetAsmJsFunctionInfo()->mTJBeginAddress = buffer;

            if (buffer == nullptr)
            {
                Js::Throw::OutOfMemory();
            }

            if (!GetCodeGenAllocator()->emitBufferManager.CommitBuffer(allocation, buffer, codeSize, mEncodeBuffer))
            {
                Js::Throw::OutOfMemory();
            }

            functionBody->GetScriptContext()->GetThreadContext()->SetValidCallTargetForCFG(buffer);

            // TODO: improve this once EntryPoint cleanup work is complete!
#if 0
            const char16 *const functionName = functionBody->GetDisplayName();
            const char16 *const suffix = _u("TJ");
            char16 functionNameArray[256];
            const size_t functionNameCharLength = functionBody->GetDisplayNameLength();
            wcscpy_s(functionNameArray, 256, functionName);
            wcscpy_s(&functionNameArray[functionNameCharLength], 256 - functionNameCharLength, suffix);
#endif
            JS_ETW(EventWriteMethodLoad(functionBody->GetScriptContext(),
                (void *)buffer,
                codeSize,
                EtwTrace::GetFunctionId(functionBody),
                0 /* methodFlags - for future use*/,
                MethodType_Jit,
                EtwTrace::GetSourceId(functionBody),
                functionBody->GetLineNumber(),
                functionBody->GetColumnNumber(),
                functionBody->GetDisplayName()));
            entryPointInfo->SetTJCodeGenDone(); // set the codegen to done state for TJ
            entryPointInfo->SetCodeSize(codeSize);
            return buffer;
        }
        return nullptr;
    }