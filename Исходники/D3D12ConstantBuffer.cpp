bool D3D12ConstantBuffer::updateModelMatrix(Matrix4f const &data)
{
    struct  ModelMatrix
    {
        DirectX::XMFLOAT4X4 model;
        DirectX::XMFLOAT4X4 modelNormal;
    }       model;

    Matrix4f    modelNormal = data.inverse().transpose();

    for (unsigned int x = 0; x < 4; x++)
        for (unsigned int y = 0; y < 4; y++)
            model.model.m[x][y] = data(x + 1, y + 1);

    for (unsigned int x = 0; x < 4; x++)
        for (unsigned int y = 0; y < 4; y++)
            model.modelNormal.m[x][y] = modelNormal(x + 1, y + 1);

    return (update(sizeof(model), &model));
}