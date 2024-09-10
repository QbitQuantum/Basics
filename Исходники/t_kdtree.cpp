/*---------------------------------------------------------------------------*/
__m256 TTriangle::THit::HitTest8(__m256 mask, const TPoint8& orig, const D3DXVECTOR3& d, HitResult8* result) const
{
    int u, v, w;
    w = ci;
    u = w == 0 ? 1 : 0;
    v = w == 2 ? 1 : 2;

    __m256 nu = _mm256_broadcast_ss(&this->nu);
    __m256 np = _mm256_broadcast_ss(&this->np);
    __m256 nv = _mm256_broadcast_ss(&this->nv);
    __m256 pu = _mm256_broadcast_ss(&this->pu);
    __m256 pv = _mm256_broadcast_ss(&this->pv);
    __m256 e0u = _mm256_broadcast_ss(&this->e0u);
    __m256 e0v = _mm256_broadcast_ss(&this->e0v);
    __m256 e1u = _mm256_broadcast_ss(&this->e1u);
    __m256 e1v = _mm256_broadcast_ss(&this->e1v);

    __m256 ou = orig[u];
    __m256 ov = orig[v];
    __m256 ow = orig[w];
    __m256 du = _mm256_broadcast_ss(&d[u]);
    __m256 dv = _mm256_broadcast_ss(&d[v]);
    __m256 dw = _mm256_broadcast_ss(&d[w]);

    __m256 dett = np -(ou*nu+ov*nv+ow);
    __m256 det = du*nu+dv*nv+dw;
    __m256 Du = du*dett - (pu-ou)*det;
    __m256 Dv = dv*dett - (pv-ov)*det;
    __m256 detu = (e1v*Du - e1u*Dv);
    __m256 detv = (e0u*Dv - e0v*Du);

    __m256 tmpdet0 = det - detu - detv;

    __m256 detMask = _mm256_xor_ps(_mm256_xor_ps(tmpdet0, detv) | _mm256_xor_ps(detv, detu), g_one8) > _mm256_setzero_ps();

    mask = mask & detMask;

    __m256 rdet = _mm256_rcp_ps(det);

    result->t = dett * rdet;
    result->u = detu * rdet;
    result->v = detv * rdet;

    return mask & (result->t > _mm256_setzero_ps());
    /**/
}