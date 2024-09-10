HRESULT CompileShader( const char* Source,
                       LPCSTR strFunctionName,
                       const D3D_SHADER_MACRO* pDefines, 
                       IShaderSourceInputStreamFactory *pIncludeStreamFactory,
                       LPCSTR profile, 
                       ID3DBlob **ppBlobOut )
{
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#else
    // Warning: do not use this flag as it causes shader compiler to fail the compilation and 
    // report strange errors:
    // dwShaderFlags |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif
	HRESULT hr;
	do
	{
        CComPtr<ID3DBlob> errors;
        auto SourceLen = strlen(Source);
         
        D3DIncludeImpl IncludeImpl(pIncludeStreamFactory);
        hr = D3DCompile( Source, SourceLen, NULL, pDefines, &IncludeImpl, strFunctionName, profile, dwShaderFlags, 0, ppBlobOut, &errors );
       
		if( FAILED(hr) || errors )
		{
            std::wstringstream errorss;
            ComErrorDesc ErrDesc(hr);
            if( FAILED(hr) )
                Diligent::FormatMsg( errorss, "Failed to compile shader\n" );
            else
                Diligent::FormatMsg( errorss, "Shader compiler output:\n" );
            Diligent::FormatMsg( errorss, ErrDesc.Get(), "\n" );
            if( errors )
                Diligent::FormatMsg( errorss, (char*)errors->GetBufferPointer() );
            auto ErrorDesc = errorss.str();
            OutputDebugStringW( ErrorDesc.c_str() );
			if( FAILED(hr) 
#ifdef PLATFORM_WIN32
                && IDRETRY != MessageBoxW( NULL, ErrorDesc.c_str() , L"FX Error", MB_ICONERROR | (Source == nullptr ? MB_ABORTRETRYIGNORE : 0) ) 
#endif
                )
			{
				break;
			}
		}
	} while( FAILED(hr) );
	return hr;
}