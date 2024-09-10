_Use_decl_annotations_
void KdTreeCompiler2::SplitEdge(_In_ const StaticGeometryVertex& v0, _In_ const StaticGeometryVertex& v1, uint32_t axis, float value, _Out_ StaticGeometryVertex* v)
{
    XMFLOAT3 vv0 = v0.Position;
    XMFLOAT3 vv1 = v1.Position;

    float d0 = *(&vv0.x + axis) - value;

    XMVECTOR sub = XMVectorSubtract(XMLoadFloat3(&vv1), XMLoadFloat3(&vv0));
    XMVECTOR dir = XMVector3Normalize(sub);
    XMVECTOR n = XMLoadFloat3(&_normals[axis]);
    float d = d0;
    if (d > 0)
    {
        n = XMVectorNegate(n);
    }
    else if (d < 0)
    {
        d = -d;
    }
    else
    {
        assert(false);
    }

    float x = d / XMVectorGetX(XMVector3Dot(n, dir));
    XMStoreFloat3(&v->Position, XMVectorAdd(XMLoadFloat3(&vv0), XMVectorScale(dir, x)));
}