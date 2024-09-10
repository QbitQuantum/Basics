D3D11Context::ShaderCompileResult D3D11Context::compileShader (const ShaderCompileDesc& desc)
{
    size_t sourceSize = desc.sourceSize;
    if (0 == sourceSize)
        sourceSize = strlen (desc.source);

    Hold<ID3DBlob> bytecode;
    Hold<ID3DBlob> error;

    if (FAILED (D3DCompile2 (desc.source, sourceSize, desc.name, desc.defines, desc.include, desc.entry, desc.target, desc.flags1, desc.flags2, desc.secondaryDataFlags, desc.secondaryData, desc.secondaryDataSize, bytecode, error)))
    {
        return ShaderCompileResult (nullptr, error.drop());
    }

    return ShaderCompileResult (bytecode.drop(), error.drop());
}