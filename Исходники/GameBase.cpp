bool GameBase::LineSphereHitTest(Mesh* mesh, const XMFLOAT3* p0, const XMFLOAT3* dir, float& outT)
{
    XMFLOAT3 center(mesh->Extents().CenterX, mesh->Extents().CenterY, mesh->Extents().CenterZ);
    BoundingSphere* sphere = new BoundingSphere(center, mesh->Extents().Radius);
    return sphere->Intersects(XMLoadFloat3(p0), XMLoadFloat3(dir), outT);
}