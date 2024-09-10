	//-----------------------------------------------------------------------
	void D3D10HLSLProgram::loadFromSource(void)
	{
		class HLSLIncludeHandler : public ID3D10Include
		{
		public:
			HLSLIncludeHandler(Resource* sourceProgram) 
				: mProgram(sourceProgram) {}
			~HLSLIncludeHandler() {}

			STDMETHOD(Open)(D3D10_INCLUDE_TYPE IncludeType,
				LPCSTR pFileName,
				LPCVOID pParentData,
				LPCVOID *ppData,
				UINT *pByteLen
				)
			{
				// find & load source code
				DataStreamPtr stream = 
					ResourceGroupManager::getSingleton().openResource(
					String(pFileName), mProgram->getGroup(), true, mProgram);

				String source = stream->getAsString();
				// copy into separate c-string
				// Note - must NOT copy the null terminator, otherwise this will terminate
				// the entire program string!
				*pByteLen = static_cast<UINT>(source.length());
				char* pChar = new char[*pByteLen];
				memcpy(pChar, source.c_str(), *pByteLen);
				*ppData = pChar;

				return S_OK;
			}

			STDMETHOD(Close)(LPCVOID pData)
			{
				char* pChar = (char*)pData;
				delete [] pChar;
				return S_OK;
			}
		protected:
			Resource* mProgram;


		};

		// include handler
		HLSLIncludeHandler includeHandler(this);

		ID3D10Blob * errors = 0;

		/*String profile; // Instruction set to be used when generating code. Possible values: "vs_4_0", "ps_4_0", or "gs_4_0".
		switch(mType)
		{
		case GPT_VERTEX_PROGRAM:
			profile = "vs_4_0";
			break;
		case GPT_FRAGMENT_PROGRAM:
			profile = "ps_4_0";
			break;
		}*/

		HRESULT hr = D3DX10CompileFromMemory(
			mSource.c_str(),	// [in] Pointer to the shader in memory. 
			mSource.size(),		// [in] Size of the shader in memory.  
			NULL,				// [in] The name of the file that contains the shader code. 
			NULL,				// [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D10_SHADER_MACRO. If not used, set this to NULL. 
			&includeHandler,	// [in] Optional. Pointer to an ID3D10Include Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
			mEntryPoint.c_str(), // [in] Name of the shader-entrypoint function where shader execution begins. 
			mTarget.c_str(),			// [in] A string that specifies the shader model; can be any profile in shader model 2, shader model 3, or shader model 4. 
			0,				// [in] Effect compile flags - no D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY at the first try...
			NULL,				// [in] Effect compile flags
			NULL,				// [in] A pointer to a thread pump interface (see ID3DX10ThreadPump Interface). Use NULL to specify that this function should not return until it is completed. 
			&mpMicroCode,		// [out] A pointer to an ID3D10Blob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
			&errors,			// [out] A pointer to an ID3D10Blob Interface which contains a listing of errors and warnings that occured during compilation. These errors and warnings are identical to the the debug output from a debugger.
			NULL				// [out] A pointer to the return value. May be NULL. If pPump is not NULL, then pHResult must be a valid memory location until the asynchronous execution completes. 
			);

		if (FAILED(hr)) // if fails - try with backwards compatibility flag
		{
			hr = D3DX10CompileFromMemory(
				mSource.c_str(),	// [in] Pointer to the shader in memory. 
				mSource.size(),		// [in] Size of the shader in memory.  
				NULL,				// [in] The name of the file that contains the shader code. 
				NULL,				// [in] Optional. Pointer to a NULL-terminated array of macro definitions. See D3D10_SHADER_MACRO. If not used, set this to NULL. 
				&includeHandler,	// [in] Optional. Pointer to an ID3D10Include Interface interface for handling include files. Setting this to NULL will cause a compile error if a shader contains a #include. 
				mEntryPoint.c_str(), // [in] Name of the shader-entrypoint function where shader execution begins. 
				mTarget.c_str(),			// [in] A string that specifies the shader model; can be any profile in shader model 2, shader model 3, or shader model 4. 
				D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY,				// [in] Effect compile flags - D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY enables older shaders to compile to 4_0 targets
				NULL,				// [in] Effect compile flags
				NULL,				// [in] A pointer to a thread pump interface (see ID3DX10ThreadPump Interface). Use NULL to specify that this function should not return until it is completed. 
				&mpMicroCode,		// [out] A pointer to an ID3D10Blob Interface which contains the compiled shader, as well as any embedded debug and symbol-table information. 
				&errors,			// [out] A pointer to an ID3D10Blob Interface which contains a listing of errors and warnings that occured during compilation. These errors and warnings are identical to the the debug output from a debugger.
				NULL				// [out] A pointer to the return value. May be NULL. If pPump is not NULL, then pHResult must be a valid memory location until the asynchronous execution completes. 
				);

		}


#if 0 // this is how you disassemble
		LPCSTR commentString = NULL;
		ID3D10Blob* pIDisassembly = NULL;
		char* pDisassembly = NULL;
		if( mpMicroCode )
		{
			D3D10DisassembleShader( (UINT*) mpMicroCode->GetBufferPointer(), 
				mpMicroCode->GetBufferSize(), TRUE, commentString, &pIDisassembly );
		}

		const char* assemblyCode =  static_cast<const char*>(pIDisassembly->GetBufferPointer());
#endif
		if (FAILED(hr))
		{
			mErrorsInCompile = true;
			String message = "Cannot assemble D3D10 high-level shader " + mName + " Errors:\n" +
				static_cast<const char*>(errors->GetBufferPointer());
			errors->Release();
			OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, message,
				"D3D10HLSLProgram::loadFromSource");
		}

		SIZE_T BytecodeLength = mpMicroCode->GetBufferSize();

// this is a temp patch for the nov 08 DX SDK
#ifdef D3DX10ReflectShader 
		hr = D3DX10ReflectShader( (void*) mpMicroCode->GetBufferPointer(), BytecodeLength,
			&mpIShaderReflection );
#else
		hr = D3D10ReflectShader( (void*) mpMicroCode->GetBufferPointer(), BytecodeLength,
			&mpIShaderReflection );
#endif

		if (!FAILED(hr))
		{
			hr = mpIShaderReflection->GetDesc( &mShaderDesc );

			if (!FAILED(hr))
			{
				if (mShaderDesc.ConstantBuffers == 1)
				{
					mShaderReflectionConstantBuffer = mpIShaderReflection->GetConstantBufferByIndex(0);


					hr = mShaderReflectionConstantBuffer->GetDesc(&mConstantBufferDesc);

					createConstantBuffer(mConstantBufferDesc.Size);

					for(unsigned int i = 0; i < mConstantBufferDesc.Variables ; i++)
					{

						ID3D10ShaderReflectionVariable* varRef;
						varRef = mShaderReflectionConstantBuffer->GetVariableByIndex(i);

						D3D10_SHADER_VARIABLE_DESC shaderVerDesc;
						HRESULT hr = varRef->GetDesc(&shaderVerDesc);

						ShaderVarWithPosInBuf newVar;
						newVar.var = shaderVerDesc;
						newVar.wasInit = false;


						mShaderVars.push_back(newVar);
					}
				}
			}
		}

		switch(mType)
		{
		case GPT_VERTEX_PROGRAM:
			CreateVertexShader();
			break;
		case GPT_FRAGMENT_PROGRAM:
			CreatePixelShader();
			break;
		}
	}