void CreateRootSignature(ID3D12RootSignature** rootSignature, const D3D12_ROOT_SIGNATURE_DESC1& desc)
{
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC versionedDesc = { };
    versionedDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    versionedDesc.Desc_1_1 = desc;

    ID3DBlobPtr signature;
    ID3DBlobPtr error;
    HRESULT hr = D3D12SerializeVersionedRootSignature(&versionedDesc, &signature, &error);
    if(FAILED(hr))
    {
        const char* errString = error ? reinterpret_cast<const char*>(error->GetBufferPointer()) : "";

        #if UseAsserts_
            AssertMsg_(false, "Failed to create root signature: %s", errString);
        #else
            throw DXException(hr, MakeString(L"Failed to create root signature: %s", errString).c_str());
        #endif
    }

    DXCall(DX12::Device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(rootSignature)));
}