	bool CShaderHLSL::Create(P3D::sShaderDesc &desc)
	{
		const char *pData;
		ULONG fsize;
		IFileSystem* pFS = CRenderer::mEngine()->mFilesystem();
		wchar path[P3DMAX_PATH];
		wsprintf(path, P3DMAX_PATH-1, _W("shaders/%s.rshader"), desc.ShaderFile.Get());
		FSFILE *fp = pFS->Load(path, (BYTE *&)pData, fsize, true);
		if (!fp)
		{
			CON(MSG_ERR, _W("Can't open %s.hlsl shader file from data/shaders directory!"), desc.ShaderFile.Get());
			return false;
		}

		ID3D10Blob *pShaderBlob = NULL;
		ID3D10Blob *pErrors = NULL;
		UINT flags = D3D10_SHADER_DEBUG;  //D3D10_SHADER_OPTIMIZATION_LEVEL3

		char profile[128];
		switch(desc.ShaderType)
		{
		case SHADERTYPE_VERTEX_SHADER:
			strcpy(profile, D3D10GetVertexShaderProfile(g_pD3ddev));
			break;
		case SHADERTYPE_GEOMETRY_SHADER:
			strcpy(profile, D3D10GetGeometryShaderProfile(g_pD3ddev));
			break;
		case SHADERTYPE_PIXEL_SHADER:
			strcpy(profile, D3D10GetPixelShaderProfile(g_pD3ddev));
			break;
		default:
			CON(MSG_ERR, _W("Chader creation failed. No apropriate ShaderType given."));
			return false;
		}

		CIncludeHandler includeHandler;
		
		D3D10_SHADER_MACRO Shader_Macros[] = 
		{
			{ "DX10", NULL },
			{ "SM4", NULL },
			NULL
		};

		if(!CheckHRResult(D3DX10CompileFromMemory(
			pData, 
			fsize, 
			NULL, 
			Shader_Macros, 
			&includeHandler, 
			_W2A(desc.EntryFunction.Get()), 
			profile, 
			flags,
			0,
			NULL,
			&pShaderBlob, 
			&pErrors,
			NULL
			)))
		{
			if(pErrors) CON(MSG_ERR, _W("%s"), _A2W((char*)pErrors->GetBufferPointer()));
			else CON(MSG_ERR, _W("Error description not given"));
			CON(MSG_ERR, _W("Shader %s could not be compiled"), desc.ShaderFile.Get());
			SAFE_RELEASE(pErrors);
			return false;
		}

		pFS->UnLoad(fp, (BYTE *)pData);

		//save to cache
		fp = pFS->Open(_W("cache/shaders/hlsl"), _W("wb"));
		const char* cs = (const char*)pShaderBlob->GetBufferPointer();
		pFS->Write(cs, 1, pShaderBlob->GetBufferSize(), fp);
		pFS->Close(fp);

		bool shaderCreated = false;
		switch(desc.ShaderType)
		{
		case SHADERTYPE_VERTEX_SHADER:
			shaderCreated = CheckHRResult(g_pD3ddev->CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &m_pVS));
			break;
		case SHADERTYPE_GEOMETRY_SHADER:
			shaderCreated = CheckHRResult(g_pD3ddev->CreateGeometryShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &m_pGS));
			break;
		case SHADERTYPE_PIXEL_SHADER:
			shaderCreated = CheckHRResult(g_pD3ddev->CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &m_pPS));
			break;
		}
		
		if(!shaderCreated)
		{
			CON(MSG_ERR, _W("Shader creation error"));
			return false;
		}

		//if(!CheckHRResult(D3DReflect((DWORD*)pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), __uuidof(ID3D10ShaderReflection), &m_pReflection)))
		if(!CheckHRResult(D3D10ReflectShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), &m_pReflection)))
		{
			CON(MSG_ERR, _W("Could not create a Shader reflection"));
			return false;
		}
		//HRESULT D3DReflect(LPCVOID pSrcData, SIZE_T SrcDataSize, REFIID pInterface,	void **ppReflector);
		D3D10_SHADER_DESC shDesc;
		m_pReflection->GetDesc(&shDesc);
		m_numResources = shDesc.BoundResources; //not sure about this

		if(desc.ShaderType == SHADERTYPE_VERTEX_SHADER)
			m_pVertDecl = new CVertexDeclaration(CRenderer::cGraphicsManager()->GetVertexDescByID(desc.VertexDescID), pShaderBlob);
		
		SAFE_RELEASE(pShaderBlob);

		m_desc = desc;

		CON(MSG_INFO, _W("Shader '%s' created"), desc.ShaderFile);
		
		return true;
	}