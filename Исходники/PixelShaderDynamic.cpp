HRESULT PixelShaderDynamic::InitShaderReflection(const void* pShaderBytecode, SIZE_T unBytecodeLength)
{
	if(m_pReflector)
	{
		m_pReflector->Release();
		m_pReflector = nullptr;
	}

	HRESULT retVal = S_OK;
	
	retVal = D3DReflect(pShaderBytecode, unBytecodeLength, IID_ID3D11ShaderReflection, (void**)&m_pReflector);

	if(FAILED(retVal))
	{
		MessageBox(NULL, L"Failed To Create Pixel Shader Reflection (Dynamic Linked PS)" , L"", MB_OK | MB_ICONERROR);
		return retVal;
	}

	UINT unNumInterfaces = m_pReflector->GetNumInterfaceSlots();
	m_vInterfaceNames.resize(unNumInterfaces);

	m_pDynamicLinkageArray = (ID3D11ClassInstance**)calloc(unNumInterfaces, sizeof(ID3D11ClassInstance*));

	if(!m_pDynamicLinkageArray)
	{
		MessageBox(NULL, L"Not Enough Memory to Allocate Dynamic Linkage Array (Pixel Shader)" , L"", MB_OK | MB_ICONERROR);
		return E_FAIL;
	}

	return S_OK;
}