void CubeMesh::Draw(RenderContext& context)
{
#if defined(DEBUG_OBB)
    context.SetRasterizerState(m_rasterType);
    context.ApplyShader(m_useShaderType);

    context.GetDeviceContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context.GetDeviceContext().IASetVertexBuffers(0, 1, &m_pVB, &m_Stride, &m_Offset);
    context.GetDeviceContext().IASetIndexBuffer(m_pIB, DXGI_FORMAT_R16_UINT, m_Offset);

    // Set constants
    cbWorld wbuffer = { XMMatrixTranspose(m_World) };
    cbInvTransposeWorld invTransWorld = { MatrixInverseTranspose(m_World) };
    cbMatTexPerObject matTexPerObject = { *m_texture->GetTextureCoordinateMatrix(), m_material };

    if (m_useShaderType == ShaderType_LightTexture)
    {
        LightTextureShader* lightTexShader = (LightTextureShader*)context.GetShader(ShaderType_LightTexture);
        lightTexShader->setCBWorld(context.GetDeviceContext(), &wbuffer);
        lightTexShader->setCBInvTransposeMatrix(context.GetDeviceContext(), &invTransWorld);
        lightTexShader->setCBMatTexPerObject(context.GetDeviceContext(), &matTexPerObject);
        lightTexShader->setTexture2D(context.GetDeviceContext(), m_texture->GetTextureResource());
    }
    else
    {
        //Solid Shader
        SolidColorShader* solidColorShader = (SolidColorShader*)context.GetShader(ShaderType_SolidColor);
        solidColorShader->setCBWorld(context.GetDeviceContext(), wbuffer);
    }

    context.DrawIndexedInstanced(36);
#endif
}