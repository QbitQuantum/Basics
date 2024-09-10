void ShaderBase::InitUniforms(ID3D10Blob* s)
{
    ID3D10ShaderReflection* ref = NULL;
    D3D10ReflectShader(s->GetBufferPointer(), s->GetBufferSize(), &ref);
    ID3D10ShaderReflectionConstantBuffer* buf = ref->GetConstantBufferByIndex(0);
    D3D10_SHADER_BUFFER_DESC bufd;
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
        ID3D10ShaderReflectionVariable* var = buf->GetVariableByIndex(i);
        if (var)
        {
            D3D10_SHADER_VARIABLE_DESC vd;
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