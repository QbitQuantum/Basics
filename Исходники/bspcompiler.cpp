_Use_decl_annotations_
void BspCompiler::SplitEdge(const Vertex& v0, const Vertex& v1, const XMFLOAT4& plane, Vertex* v)
{
    XMFLOAT3 vv0 = v0.Position;
    XMFLOAT3 vv1 = v1.Position;

    float d0 = DistToPlane(plane, vv0);

    XMVECTOR sub = XMVectorSubtract(XMLoadFloat3(&vv1), XMLoadFloat3(&vv0));
    XMVECTOR dir = XMVector3Normalize(sub);
    XMVECTOR n = XMLoadFloat4(&plane);
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