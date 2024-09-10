GenerateMipsHelper::GenerateMipsHelper(ID3D12Device *pd3d12Device)
{
    CD3DX12_ROOT_PARAMETER Params[3];
    Params[0].InitAsConstants(4, 0);
    CD3DX12_DESCRIPTOR_RANGE SRVRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
    Params[1].InitAsDescriptorTable(1, &SRVRange);
    CD3DX12_DESCRIPTOR_RANGE UAVRange(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 4, 0);
    Params[2].InitAsDescriptorTable(1, &UAVRange);
    CD3DX12_STATIC_SAMPLER_DESC SamplerLinearClampDesc(
        0, D3D12_FILTER_MIN_MAG_MIP_LINEAR, D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP, D3D12_TEXTURE_ADDRESS_MODE_CLAMP);
    CD3DX12_ROOT_SIGNATURE_DESC RootSigDesc;
    RootSigDesc.NumParameters = _countof(Params);
    RootSigDesc.pParameters = Params;
    RootSigDesc.NumStaticSamplers = 1;
    RootSigDesc.pStaticSamplers = &SamplerLinearClampDesc;
    RootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;

    CComPtr<ID3DBlob> signature;
    CComPtr<ID3DBlob> error;
    HRESULT hr = D3D12SerializeRootSignature(&RootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    hr = pd3d12Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), __uuidof(m_pGenerateMipsRS), reinterpret_cast<void**>( static_cast<ID3D12RootSignature**>(&m_pGenerateMipsRS)));
    CHECK_D3D_RESULT_THROW(hr, "Failed to create root signature for mipmap generation")

    D3D12_COMPUTE_PIPELINE_STATE_DESC PSODesc = {};
    PSODesc.pRootSignature = m_pGenerateMipsRS;
    PSODesc.NodeMask = 0;
    PSODesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

#define CreatePSO(PSO, ShaderByteCode) \
        PSODesc.CS.pShaderBytecode = ShaderByteCode;\
        PSODesc.CS.BytecodeLength = sizeof(ShaderByteCode);\
        hr = pd3d12Device->CreateComputePipelineState(&PSODesc, __uuidof(PSO), reinterpret_cast<void**>( static_cast<ID3D12PipelineState**>(&PSO))); \
        CHECK_D3D_RESULT_THROW(hr, "Failed to create Pipeline state for mipmap generation")

    CreatePSO(m_pGenerateMipsLinearPSO[0], g_pGenerateMipsLinearCS);
    CreatePSO(m_pGenerateMipsLinearPSO[1], g_pGenerateMipsLinearOddXCS);
    CreatePSO(m_pGenerateMipsLinearPSO[2], g_pGenerateMipsLinearOddYCS);
    CreatePSO(m_pGenerateMipsLinearPSO[3], g_pGenerateMipsLinearOddCS);
    CreatePSO(m_pGenerateMipsGammaPSO[0], g_pGenerateMipsGammaCS);
    CreatePSO(m_pGenerateMipsGammaPSO[1], g_pGenerateMipsGammaOddXCS);
    CreatePSO(m_pGenerateMipsGammaPSO[2], g_pGenerateMipsGammaOddYCS);
    CreatePSO(m_pGenerateMipsGammaPSO[3], g_pGenerateMipsGammaOddCS);
}