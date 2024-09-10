void
Projector::updateOrientation()
{
    float3 kNormal = make_float3(0.0f, 1.0f, 0.0f);

    Plane kBasePlane = Plane(make_float3(0.0f, 0.0f, 0.0f), kNormal);
    Plane kUpperPlane = Plane(kNormal, m_fUpperLimit);
    Plane kLowerPlane = Plane(kNormal, m_fLowerLimit);

    m_kUp = m_pkCamera->getUpDirection(); 
    m_kView = m_pkCamera->getViewDirection();
    m_kPosition = m_pkCamera->getPosition();
    m_kLookAt = m_kPosition + m_kView;

    if(m_bSimple)
    {
        m_kUp = make_float3(0.0f, 1.0f, 0.0f);
        m_kPosition = m_kPosition - m_kView * 5.0f;
        m_kLookAt = m_kPosition + m_kView;
    }
    else
    {   
        float fHeight = kLowerPlane.distance(m_kPosition);

        bool bBelow = fHeight < 0.0f;

        if(fHeight < (m_fStrength + m_fElevation))
        {
            if(bBelow)
            {
                m_kPosition += kNormal * ((m_fStrength + m_fElevation) - 2.0f * fHeight);
            }
            else
            {
                m_kPosition += kNormal * ((m_fStrength + m_fElevation) - fHeight);        
            }
        }
        
        if (!kBasePlane.findIntersection(m_kLookAt, m_kPosition, m_kPosition + m_kView))
        {
            float3 kFlip = m_kView - kNormal * dot(m_kView, kNormal) * 2.0f;
            kBasePlane.findIntersection(m_kLookAt, m_kPosition, m_kPosition + kFlip);
        }

        float fD = fabs( kBasePlane.dotNormal(m_kView) );
        float fZ = (m_pkCamera->getFarClip() - m_pkCamera->getNearClip()) * 0.5f;
        
        float3 kAim = (m_kPosition + m_kView * fZ);
        kAim = kAim - kNormal * dot(kAim, kNormal);
        
        m_kLookAt = ((m_kLookAt * fD + kAim * (1.0f - fD)));
        m_kView = (m_kLookAt - m_kPosition);
    }
}