bool TSRD3D11Effect::Compile( const char* _pFileName, const char* _pSuffix, TSRShaderMacro* _pMacros )
{
#ifdef D3D10_RENDERER
    const char* pVersionName = "fx_4_0";
#elif defined ( D3D11_RENDERER )
    const char* pVersionName = "fx_5_0";

	TSRD3D11GraphicsSubSystem* pD3D11GraphicsSubSystem = ( TSRD3D11GraphicsSubSystem* ) Graphics();
	
	switch ( pD3D11GraphicsSubSystem->m_FeatureLevel )
	{
	case D3D_FEATURE_LEVEL_11_0:
		pVersionName = "fx_5_0";
		break;
	case D3D_FEATURE_LEVEL_10_1:
	//	pVersionName = "fx_4_1";
		//break;
	case D3D_FEATURE_LEVEL_10_0:
		pVersionName = "fx_4_0";
		break;
	case D3D_FEATURE_LEVEL_9_3:
	case D3D_FEATURE_LEVEL_9_2:
	case D3D_FEATURE_LEVEL_9_1:
		pVersionName = "fx_3_0";
		break;
	}
	
#endif 

    D3D_SHADER_MACRO* pMacros = ( D3D_SHADER_MACRO* ) _pMacros;

    // formulate the compiled shader name...
    string compiledShaderName = "cache/";
    compiledShaderName        += _pFileName;
    compiledShaderName        += ".";
    compiledShaderName        += pVersionName;
    compiledShaderName        += _pSuffix;
    compiledShaderName        += ".fxobj";

    
#ifdef ALWAYS_COMPILE_SHADERS
    bool NeedToCompile = true;
#else
    bool NeedToCompile = TSRFileSystem::FileNeedsRebuild( _pFileName, compiledShaderName.c_str() );
#endif // ALWAYS_COMPILE_SHADERS

#ifndef NEVER_COMPILE_SHADERS
	 
    if ( NeedToCompile )
    {
        ID3D10Blob* pErrors = 0;
        DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;// | D3D10_SHADER_DEBUG;

        // compile the source...
#if defined( D3D11_RENDERER ) && !defined( LEGACY_D3D11 )
		pVersionName = "fx_5_0";
		wchar_t wFileName[ 256 ];
		MultiByteToWideChar( CP_ACP, 0, _pFileName, -1, wFileName, 1000 );
		HRESULT hr = D3DCompileFromFile( wFileName, pMacros, D3D_COMPILE_STANDARD_FILE_INCLUDE, 0, pVersionName, dwShaderFlags, 0, &m_pEffectBuffer, &pErrors );
#else
        HRESULT hr = D3DCompileFromFile( _pFileName, pMacros, 0, 0, pVersionName, dwShaderFlags, 0, NULL, &m_pEffectBuffer, &pErrors, NULL );
#endif 
        if( FAILED( hr ) )
        {
            TSRPrintln( "Failed to compile effect %s", _pFileName );
            TSRPrintln( ( char* ) pErrors->GetBufferPointer() );
            return false;
        }
#ifdef _DEBUG
        // save the effect blob...to cache it...
        TSRFileStream* fpNewCompiledShader = TSRFileSystem::OpenFileStream( compiledShaderName.c_str(), "w+b" );
        int bufferSize = ( int ) m_pEffectBuffer->GetBufferSize();
        fwrite( m_pEffectBuffer->GetBufferPointer(), bufferSize, 1, fpNewCompiledShader );
        fclose( fpNewCompiledShader );
#endif
    }
    // load the already precompiled blob
    else
#endif // NEVER_COMPILE_SHADER
    {
        TSRFileStream* fp = TSRFileSystem::OpenFileStream( compiledShaderName.c_str(), "rb" );
        int bufferSize = fp->GetSize();
#if defined( D3D11_RENDERER )
		D3DCreateBlob( bufferSize, &m_pEffectBuffer );
#else
        D3D10CreateBlob( bufferSize, &m_pEffectBuffer );
#endif
        fread( m_pEffectBuffer->GetBufferPointer(), bufferSize, 1, fp );
        fclose( fp );
    }

    // create the actual effect from the blob and start inspecting the constants used inside it..
#ifdef D3D10_RENDERER
    HRESULT hr = D3D10CreateEffectFromMemory( m_pEffectBuffer->GetBufferPointer(), m_pEffectBuffer->GetBufferSize(), 0, g_pD3DDevice, 0, &m_pD3DEffect );
#endif 

#ifdef D3D11_RENDERER
    HRESULT hr = D3DX11CreateEffectFromMemory( m_pEffectBuffer->GetBufferPointer(), m_pEffectBuffer->GetBufferSize(), 0, g_pD3DDevice, &m_pD3DEffect );
#endif

    if ( FAILED( hr ) )
    {
        TSRPrintln( "Failed to create effect %s from memory", _pFileName );
    }
    BindConstants();
    return true;
}