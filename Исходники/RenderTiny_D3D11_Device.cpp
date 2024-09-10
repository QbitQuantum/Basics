void ShaderBase::InitUniforms(void* s, size_t size)
{
    ID3D11ShaderReflection* ref = NULL;
    D3DReflect(s, size, IID_ID3D11ShaderReflection, (void**) &ref);
    ID3D11ShaderReflectionConstantBuffer* buf = ref->GetConstantBufferByIndex(0);
    D3D11_SHADER_BUFFER_DESC bufd;
    if (FAILED(buf->GetDesc(&bufd)))
    {
        UniformsSize = 0;
        if (UniformData)
        {
            OVR_FREE(UniformData);
            UniformData = 0;
        }
        return;
    }

    for(unsigned i = 0; i < bufd.Variables; i++)
    {
        ID3D11ShaderReflectionVariable* var = buf->GetVariableByIndex(i);
        if (var)
        {
            D3D11_SHADER_VARIABLE_DESC vd;
            if (SUCCEEDED(var->GetDesc(&vd)))
            {
                Uniform u;
                u.Name = vd.Name;
                u.Offset = vd.StartOffset;
                u.Size = vd.Size;
                UniformInfo.PushBack(u);
            }
        }
    }

    UniformsSize = bufd.Size;
    UniformData = (unsigned char*)OVR_ALLOC(bufd.Size);
}