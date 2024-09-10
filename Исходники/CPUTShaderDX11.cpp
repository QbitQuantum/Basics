//-----------------------------------------------------------------------------
bool CPUTShaderDX11::ShaderRequiresPerModelPayload( CPUTConfigBlock &properties )
{
    ID3D11ShaderReflection *pReflector = NULL;

    D3DReflect( mpBlob->GetBufferPointer(), mpBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);
    // Walk through the shader input bind descriptors.
    // If any of them begin with '@', then we need a unique material per model (i.e., we need to clone the material).
    int ii=0;
    D3D11_SHADER_INPUT_BIND_DESC desc;
    HRESULT hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    while( SUCCEEDED(hr) )
    {
        cString tagName = s2ws(desc.Name);
        CPUTConfigEntry *pValue = properties.GetValueByName(tagName);
        if( !pValue->IsValid() )
        {
            // We didn't find our property in the file.  Is it in the global config block?
            pValue = CPUTMaterial::mGlobalProperties.GetValueByName(tagName);
        }
        cString boundName = pValue->ValueAsString();
        if( (boundName.length() > 0) && ((boundName[0] == '@') || (boundName[0] == '#')) )
        {
            return true;
        }
        hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    }
    return false;
}