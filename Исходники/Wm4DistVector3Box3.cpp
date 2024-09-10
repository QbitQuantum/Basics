Real DistVector3Box3<Real>::GetSquared ()
{
    // work in the box's coordinate system
    Vector3<Real> kDiff = *m_pkVector - m_pkBox->Center;

    // compute squared distance and closest point on box
    Real fSqrDistance = (Real)0.0, fDelta;
    Vector3<Real> kClosest;
    int i;
    for (i = 0; i < 3; i++)
    {
        kClosest[i] = kDiff.Dot(m_pkBox->Axis[i]);
        if (kClosest[i] < -m_pkBox->Extent[i])
        {
            fDelta = kClosest[i] + m_pkBox->Extent[i];
            fSqrDistance += fDelta*fDelta;
            kClosest[i] = -m_pkBox->Extent[i];
        }
        else if (kClosest[i] > m_pkBox->Extent[i])
        {
            fDelta = kClosest[i] - m_pkBox->Extent[i];
            fSqrDistance += fDelta*fDelta;
            kClosest[i] = m_pkBox->Extent[i];
        }
    }

    m_kClosestPoint0 = *m_pkVector;
    m_kClosestPoint1 = m_pkBox->Center;
    for (i = 0; i < 3; i++)
    {
        m_kClosestPoint1 += kClosest[i]*m_pkBox->Axis[i];
    }

    return fSqrDistance;
}