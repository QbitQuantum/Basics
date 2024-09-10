HRESULT WINAPI D3D10DisassembleShader(const void *data, SIZE_T data_size,
        BOOL color_code, const char *comments, ID3D10Blob **disassembly)
{
    TRACE("data %p, data_size %#lx, color_code %#x, comments %p, disassembly %p.\n",
            data, data_size, color_code, comments, disassembly);

    return D3DDisassemble(data, data_size, color_code ? D3D_DISASM_ENABLE_COLOR_CODE : 0, comments, disassembly);
}