    void RootSignature::finalize( ID3D12Device* pDevice )
    {
        // Create the root signature description.
        CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Init( 
            static_cast<UINT>( m_rootParams.size() ), 
            m_rootParams.data(), 
            static_cast<UINT>( m_staticSamplers.size() ),
            m_staticSamplers.data(), 
            D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT );

        // TODO: Implement root signature caching.

        // Create the graphics root signature.
        ComPtr<ID3DBlob> signature;
        ComPtr<ID3DBlob> error;
        ThrowIfFailed( D3D12SerializeRootSignature( &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error ) );
        ThrowIfFailed( pDevice->CreateRootSignature( 0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS( &m_rootSignature ) ) );
    }