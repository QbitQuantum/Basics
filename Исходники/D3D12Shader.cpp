std::string D3D12Shader::Disassemble(int flags)
{
    if (!byteCode_.empty())
    {
        ComPtr<ID3DBlob> disasm;

        auto hr = D3DDisassemble(byteCode_.data(), byteCode_.size(), DXGetDisassemblerFlags(flags), nullptr, &disasm);
        DXThrowIfFailed(hr, "failed to disassemble D3D12 shader byte code");

        return DXGetBlobString(disasm.Get());
    }
    return "";
}