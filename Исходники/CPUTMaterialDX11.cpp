//-----------------------------------------------------------------------------
void CPUTMaterialDX11::ReadShaderSamplersAndTextures( ID3DBlob *pBlob, CPUTShaderParameters *pShaderParameter )
{
    // ***************************
    // Use shader reflection to get texture and sampler names.  We use them later to bind .mtl texture-specification to shader parameters/variables.
    // TODO: Currently do this only for PS.  Do for other shader types too.
    // TODO: Generalize, so easy to call for different shader types
    // ***************************
    ID3D11ShaderReflection *pReflector = NULL; 
    D3D11_SHADER_INPUT_BIND_DESC desc;

    D3DReflect( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pReflector);
    // Walk through the shader input bind descriptors.  Find the samplers and textures.
    int ii=0;
    HRESULT hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    while( SUCCEEDED(hr) )
    {
        switch( desc.Type )
        {
        case D3D_SIT_TEXTURE:
            pShaderParameter->mTextureParameterCount++;
            break;
        case D3D_SIT_SAMPLER:
            pShaderParameter->mSamplerParameterCount++;
            break;
        case D3D_SIT_CBUFFER:
            pShaderParameter->mConstantBufferParameterCount++;
            break;

        case D3D_SIT_TBUFFER:
        case D3D_SIT_STRUCTURED:
        case D3D_SIT_BYTEADDRESS:
            pShaderParameter->mBufferParameterCount++;
            break;

        case D3D_SIT_UAV_RWTYPED:
        case D3D_SIT_UAV_RWSTRUCTURED:
        case D3D_SIT_UAV_RWBYTEADDRESS:
        case D3D_SIT_UAV_APPEND_STRUCTURED:
        case D3D_SIT_UAV_CONSUME_STRUCTURED:
        case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
            pShaderParameter->mUAVParameterCount++;
            break;
        }
        hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    }

    pShaderParameter->mpTextureParameterName              = new cString[pShaderParameter->mTextureParameterCount];
    pShaderParameter->mpTextureParameterBindPoint         = new UINT[   pShaderParameter->mTextureParameterCount];
    pShaderParameter->mpSamplerParameterName              = new cString[pShaderParameter->mSamplerParameterCount];
    pShaderParameter->mpSamplerParameterBindPoint         = new UINT[   pShaderParameter->mSamplerParameterCount];
    pShaderParameter->mpBufferParameterName               = new cString[pShaderParameter->mBufferParameterCount];
    pShaderParameter->mpBufferParameterBindPoint          = new UINT[   pShaderParameter->mBufferParameterCount];
    pShaderParameter->mpUAVParameterName                  = new cString[pShaderParameter->mUAVParameterCount];
    pShaderParameter->mpUAVParameterBindPoint             = new UINT[   pShaderParameter->mUAVParameterCount];
    pShaderParameter->mpConstantBufferParameterName       = new cString[pShaderParameter->mConstantBufferParameterCount];
    pShaderParameter->mpConstantBufferParameterBindPoint  = new UINT[   pShaderParameter->mConstantBufferParameterCount];
        
    // Start over.  This time, copy the names.
    ii=0;
    UINT textureIndex = 0;
    UINT samplerIndex = 0;
    UINT bufferIndex = 0;
    UINT uavIndex = 0;
    UINT constantBufferIndex = 0;
    hr = pReflector->GetResourceBindingDesc( ii++, &desc );

    while( SUCCEEDED(hr) )
    {
        switch( desc.Type )
        {
        case D3D_SIT_TEXTURE:
            pShaderParameter->mpTextureParameterName[textureIndex] = s2ws(desc.Name);
            pShaderParameter->mpTextureParameterBindPoint[textureIndex] = desc.BindPoint;
            textureIndex++;
            break;
        case D3D_SIT_SAMPLER:
            pShaderParameter->mpSamplerParameterName[samplerIndex] = s2ws(desc.Name);
            pShaderParameter->mpSamplerParameterBindPoint[samplerIndex] = desc.BindPoint;
            samplerIndex++;
            break;
        case D3D_SIT_CBUFFER:
            pShaderParameter->mpConstantBufferParameterName[constantBufferIndex] = s2ws(desc.Name);
            pShaderParameter->mpConstantBufferParameterBindPoint[constantBufferIndex] = desc.BindPoint;
            constantBufferIndex++;
            break;
        case D3D_SIT_TBUFFER:
        case D3D_SIT_STRUCTURED:
        case D3D_SIT_BYTEADDRESS:
            pShaderParameter->mpBufferParameterName[bufferIndex] = s2ws(desc.Name);
            pShaderParameter->mpBufferParameterBindPoint[bufferIndex] = desc.BindPoint;
            bufferIndex++;
            break;
        case D3D_SIT_UAV_RWTYPED:
        case D3D_SIT_UAV_RWSTRUCTURED:
        case D3D_SIT_UAV_RWBYTEADDRESS:
        case D3D_SIT_UAV_APPEND_STRUCTURED:
        case D3D_SIT_UAV_CONSUME_STRUCTURED:
        case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
            pShaderParameter->mpUAVParameterName[uavIndex] = s2ws(desc.Name);
            pShaderParameter->mpUAVParameterBindPoint[uavIndex] = desc.BindPoint;
            uavIndex++;
            break;
        }
        hr = pReflector->GetResourceBindingDesc( ii++, &desc );
    }
}