HRESULT WINAPI D3D10CompileEffectFromMemory(void *data, SIZE_T data_size, const char *filename,
        const D3D10_SHADER_MACRO *defines, ID3D10Include *include, UINT hlsl_flags, UINT fx_flags,
        ID3D10Blob **effect, ID3D10Blob **errors)
{
    TRACE("data %p, data_size %lu, filename %s, defines %p, include %p, "
            "hlsl_flags %#x, fx_flags %#x, effect %p, errors %p.\n",
            data, data_size, wine_dbgstr_a(filename), defines, include,
            hlsl_flags, fx_flags, effect, errors);

    return D3DCompile(data, data_size, filename, defines, include,
            NULL, "fx_4_0", hlsl_flags, fx_flags, effect, errors);
}