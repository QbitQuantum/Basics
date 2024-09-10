/// 生成する
bool D3DShader::Create(DXGIManager *pDxgi)
{
    if(m_pVsh)return true;

    auto pDevice=pDxgi->GetD3DDevice();

    // vertex shader
    {
        Microsoft::WRL::ComPtr<ID3DBlob> vblob;
        HRESULT hr = CompileShaderFromFile(m_info.path, m_info.vs
                , vblob.GetAddressOf());
        if (FAILED(hr)) return false;

        hr = pDevice->CreateVertexShader(
                vblob->GetBufferPointer(), vblob->GetBufferSize()
                , NULL, m_pVsh.ReleaseAndGetAddressOf());
        if (FAILED(hr)) return false;

        // vertex shader reflection
        Microsoft::WRL::ComPtr<ID3D11ShaderReflection> pReflector;
        hr = D3DReflect(vblob->GetBufferPointer(), vblob->GetBufferSize()
                , IID_ID3D11ShaderReflection, &pReflector);
        if (FAILED(hr)) return false;

        D3D11_SHADER_DESC shaderdesc;
        pReflector->GetDesc(&shaderdesc);

        // Create InputLayout
        std::vector<D3D11_INPUT_ELEMENT_DESC> vbElement;
        for (size_t i = 0; i < shaderdesc.InputParameters; ++i){
            D3D11_SIGNATURE_PARAMETER_DESC sigdesc;
            pReflector->GetInputParameterDesc(i, &sigdesc);

            auto format = GetDxgiFormat(sigdesc.ComponentType, sigdesc.Mask);

            D3D11_INPUT_ELEMENT_DESC eledesc = {
                sigdesc.SemanticName
                , sigdesc.SemanticIndex
                , format
                , 0 // 決め打ち
                , D3D11_APPEND_ALIGNED_ELEMENT // 決め打ち
                , D3D11_INPUT_PER_VERTEX_DATA // 決め打ち
                , 0 // 決め打ち
            };
            vbElement.push_back(eledesc);
        }

        if (!vbElement.empty()){
            hr = pDevice->CreateInputLayout(&vbElement[0], vbElement.size(),
                vblob->GetBufferPointer(), vblob->GetBufferSize(), &m_pInputLayout);
            if (FAILED(hr)) return false;
        }
    }

    // pixel shader
    {
        Microsoft::WRL::ComPtr<ID3DBlob> pblob;
        auto hr = CompileShaderFromFile(m_info.path, m_info.ps
                , pblob.GetAddressOf());
        if (FAILED(hr)) return false;

        hr = pDevice->CreatePixelShader(
                pblob->GetBufferPointer(), pblob->GetBufferSize()
                , NULL, m_pPsh.ReleaseAndGetAddressOf());
        if (FAILED(hr)) return false;
    }

    return true;
}