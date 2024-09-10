PixelShader::PixelShader(wstring path)
{
    HRESULT result;

    auto shaderBuffer = Tools::ReadFileToVector(path);
    result = GetD3D11Device()->CreatePixelShader(&shaderBuffer[0], shaderBuffer.size(), nullptr, &m_Shader);
    Assert(result == S_OK);

    auto extensionIndex = path.find_last_of('.');
    auto metadataBuffer = Tools::ReadFileToVector(path.substr(0, extensionIndex + 1) + L"shadermetadata");

    Reflect(shaderBuffer, metadataBuffer);
}