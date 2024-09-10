void SpriteRenderer::Render(ID3D11ShaderResourceView* texture,
                            const XMMATRIX& transform,
                            const XMFLOAT4& color,
                            const XMFLOAT4* drawRect)
{
    _ASSERT(context);
    _ASSERT(initialized);

    D3DPERF_BeginEvent(0xFFFFFFFF, L"SpriteRenderer Render");

    // Set the vertex shader
    context->VSSetShader(vertexShader, NULL, 0);

    // Set the input layout
    context->IASetInputLayout(inputLayout);

    // Set the vertex buffer
    UINT stride = sizeof(SpriteVertex);
    UINT offset = 0;
    ID3D11Buffer* vb = vertexBuffer.GetInterfacePtr();
    context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);

    // Set per-batch constants
    D3D11_TEXTURE2D_DESC desc = SetPerBatchData(texture);

    // Set per-instance data
    SpriteDrawData perInstance;
    perInstance.Transform = XMMatrixTranspose(transform);
    perInstance.Color = color;

    // Draw rect
    if (drawRect == NULL)
        perInstance.DrawRect = XMFLOAT4(0, 0, static_cast<float>(desc.Width), static_cast<float>(desc.Height));
    else
    {
        _ASSERT(drawRect->x >= 0 && drawRect->x < desc.Width);
        _ASSERT(drawRect->y >= 0 && drawRect->y < desc.Height);
        _ASSERT(drawRect->z > 0 && drawRect->x + drawRect->z < desc.Width);
        _ASSERT(drawRect->w > 0 && drawRect->y + drawRect->w < desc.Height);
        perInstance.DrawRect = *drawRect;
    }

    // Copy in the buffer data
    D3D11_MAPPED_SUBRESOURCE mapped;
    DXCall(context->Map(vsPerInstanceCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped));
    CopyMemory(mapped.pData, &perInstance, sizeof(SpriteDrawData));
    context->Unmap(vsPerInstanceCB, 0);

    ID3D11Buffer* buffers [2] = { vsPerBatchCB, vsPerInstanceCB };
    context->VSSetConstantBuffers(0, 2, buffers);

    // Set the texture
    context->PSSetShaderResources(0, 1, &texture);

    context->DrawIndexed(6, 0, 0);

    D3DPERF_EndEvent();
}