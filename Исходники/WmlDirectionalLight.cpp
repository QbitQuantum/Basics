//----------------------------------------------------------------------------
void DirectionalLight::ComputeDiffuse (const Matrix3f& rkWorldRotate,
    const Vector3f&, float, const Vector3f*, const Vector3f* akNormal,
    int iQuantity, const bool* abVisible, ColorRGB* akDiffuse)
{
    // transform light direction to model space of old mesh
    Vector3f kModelDir = m_kDirection*rkWorldRotate;

    // adjust diffuse color by light intensity
    ColorRGB kAdjDiffuse = m_fIntensity*m_kDiffuse;

    for (int i = 0; i < iQuantity; i++)
    {
        if ( abVisible[i] )
        {
            float fDot = kModelDir.Dot(akNormal[i]);
            if ( fDot < 0.0f )
                akDiffuse[i] -= fDot*kAdjDiffuse;
        }
    }
}