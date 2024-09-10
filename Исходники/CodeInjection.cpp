/// <summary>Handle <c>ICorProfilerCallback::JITCompilationStarted</c></summary>
/// <remarks>The 'workhorse' </remarks>
HRESULT STDMETHODCALLTYPE CCodeInjection::JITCompilationStarted( 
        /* [in] */ FunctionID functionId, /* [in] */ BOOL fIsSafeToBlock) 
{
    ModuleID moduleId; mdToken funcToken;
    std::wstring methodName = GetMethodName(functionId, 
        moduleId, funcToken);
    ATLTRACE(_T("::JITCompilationStarted(%X -> %s)"), 
        functionId, W2CT(methodName.c_str()));

    if (L"ProfilerTarget.Program.OnMethodToInstrument" == methodName && 
        m_targetMethodRef !=0 ) {
        // get method body
        LPCBYTE pMethodHeader = NULL;
        ULONG iMethodSize = 0;
        COM_FAIL_RETURN(m_profilerInfo3->GetILFunctionBody(
            moduleId, funcToken, &pMethodHeader, &iMethodSize), 
            S_OK);

        CComPtr<IMetaDataEmit> metaDataEmit;
        COM_FAIL_RETURN(m_profilerInfo3->GetModuleMetaData(moduleId, 
            ofRead | ofWrite, IID_IMetaDataEmit, (IUnknown**)&metaDataEmit), S_OK);

        // parse IL
        Method instMethod((IMAGE_COR_ILMETHOD*)pMethodHeader); // <--
        instMethod.SetMinimumStackSize(3); // should be correct for this sample
        
        // NOTE: build signature (in the knowledge that the method we are instrumenting currently has no local vars)
        static COR_SIGNATURE localSignature[] = 
        {
            IMAGE_CEE_CS_CALLCONV_LOCAL_SIG,   
            0x02,                                   
            ELEMENT_TYPE_ARRAY, ELEMENT_TYPE_OBJECT, 01, 00, 00,  
            ELEMENT_TYPE_ARRAY, ELEMENT_TYPE_OBJECT, 01, 00, 00
        };
        
        mdSignature signature;
        COM_FAIL_RETURN(metaDataEmit->GetTokenFromSig(localSignature, sizeof(localSignature), &signature), S_OK);
        instMethod.m_header.LocalVarSigTok = signature;

        // insert new IL block
        InstructionList instructions; // NOTE: this IL will be different for an instance method or if the local vars signature is different
        instructions.push_back(new Instruction(CEE_NOP));
        instructions.push_back(new Instruction(CEE_LDC_I4_2));
        instructions.push_back(new Instruction(CEE_NEWARR, m_objectTypeRef));
        instructions.push_back(new Instruction(CEE_STLOC_1));
        instructions.push_back(new Instruction(CEE_LDLOC_1));
        instructions.push_back(new Instruction(CEE_LDC_I4_0));
        instructions.push_back(new Instruction(CEE_LDARG_0));
        instructions.push_back(new Instruction(CEE_STELEM_REF));
        instructions.push_back(new Instruction(CEE_LDLOC_1));
        instructions.push_back(new Instruction(CEE_LDC_I4_1));
        instructions.push_back(new Instruction(CEE_LDARG_1));
        instructions.push_back(new Instruction(CEE_STELEM_REF));
        instructions.push_back(new Instruction(CEE_LDLOC_1));
        instructions.push_back(new Instruction(CEE_STLOC_0));
        instructions.push_back(new Instruction(CEE_LDLOC_0));
        instructions.push_back(new Instruction(CEE_CALL, m_targetMethodRef));

        instMethod.InsertSequenceInstructionsAtOriginalOffset(
            0, instructions);

        instMethod.DumpIL();

        // allocate memory
        CComPtr<IMethodMalloc> methodMalloc;
        COM_FAIL_RETURN(m_profilerInfo3->GetILFunctionBodyAllocator(
            moduleId, &methodMalloc), S_OK);
        void* pNewMethod = methodMalloc->Alloc(instMethod.GetMethodSize());

        // write new method
        instMethod.WriteMethod((IMAGE_COR_ILMETHOD*)pNewMethod);
        COM_FAIL_RETURN(m_profilerInfo3->SetILFunctionBody(moduleId, 
            funcToken, (LPCBYTE) pNewMethod), S_OK);

        // update IL maps
        ULONG mapSize = instMethod.GetILMapSize();
        void* pMap = CoTaskMemAlloc(mapSize * sizeof(COR_IL_MAP));
        instMethod.PopulateILMap(mapSize, (COR_IL_MAP*)pMap);

        COM_FAIL_RETURN(m_profilerInfo3->SetILInstrumentedCodeMap(
            functionId, TRUE, mapSize, (COR_IL_MAP*)pMap), S_OK);
        CoTaskMemFree(pMap);
    }

    return S_OK;
}