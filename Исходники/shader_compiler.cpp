bool compile_hlsl_code(const char *code,bool text_asm)
{
    if(!code)
        return false;

    ID3D10Blob *compiled=compile_hlsl(code);
    if(!compiled)
        return false;

    if(text_asm)
    {
        ID3D10Blob *asm_blob;
        D3DDisassemble(compiled->GetBufferPointer(),compiled->GetBufferSize(),
                       D3D_DISASM_ENABLE_INSTRUCTION_NUMBERING,"",&asm_blob);
        if(!asm_blob)
            return false;

        fwrite(asm_blob->GetBufferPointer(),1,asm_blob->GetBufferSize(),stdout);
        asm_blob->Release();
    }
    else
        fwrite(compiled->GetBufferPointer(),1,compiled->GetBufferSize(),stdout);

    compiled->Release();
    return true;
}