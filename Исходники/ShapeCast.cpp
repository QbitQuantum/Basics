_Use_decl_annotations_
__forceinline void __vectorcall FindBarycentricCoordinates(FXMVECTOR a, FXMVECTOR b, FXMVECTOR c, FXMVECTOR p, float* s, float* r, float* t)
{
    XMVECTOR u = b - a;
    XMVECTOR v = c - a;
    XMVECTOR w = p - a;
    XMVECTOR vCrossW = XMVector3Cross(v, w);
    XMVECTOR vCrossU = XMVector3Cross(v, u);

    // Validate r is positive (should be if p is in triangle)
    assert(XMVector2GreaterOrEqual(XMVector3Dot(vCrossW, vCrossU), XMVectorZero()));

    XMVECTOR uCrossW = XMVector3Cross(u, w);
    XMVECTOR uCrossV = XMVector3Cross(u, v);

    // Validate t is positive (should be if p is in triangle)
    assert(XMVector2GreaterOrEqual(XMVector3Dot(uCrossW, uCrossV), XMVectorZero()));

    XMVECTOR denom = XMVector3Length(uCrossV);
    XMVECTOR R = XMVector3Length(vCrossW) / denom;
    XMVECTOR T = XMVector3Length(uCrossW) / denom;

    assert(XMVector2LessOrEqual(R + T, XMVectorSet(1, 1, 1, 1)));

    *r = XMVectorGetX(R);
    *t = XMVectorGetX(T);
    *s = 1 - (*r) - (*t);
}