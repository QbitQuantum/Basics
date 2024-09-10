bool IntrSegment2Box2<Real>::Test ()
{
    Vector2<Real> kDiff = m_rkSegment.Origin - m_rkBox.Center;

    Real fAWdU[2], fADdU[2], fRhs;
    fAWdU[0] = Math<Real>::FAbs(m_rkSegment.Direction.Dot(m_rkBox.Axis[0]));
    fADdU[0] = Math<Real>::FAbs(kDiff.Dot(m_rkBox.Axis[0]));
    fRhs = m_rkBox.Extent[0] + m_rkSegment.Extent*fAWdU[0];
    if (fADdU[0] > fRhs)
    {
        return false;
    }

    fAWdU[1] = Math<Real>::FAbs(m_rkSegment.Direction.Dot(m_rkBox.Axis[1]));
    fADdU[1] = Math<Real>::FAbs(kDiff.Dot(m_rkBox.Axis[1]));
    fRhs = m_rkBox.Extent[1] + m_rkSegment.Extent*fAWdU[1];
    if (fADdU[1] > fRhs)
    {
        return false;
    }

    Vector2<Real> kPerp = m_rkSegment.Direction.Perp();
    Real fLhs = Math<Real>::FAbs(kPerp.Dot(kDiff));
    Real fPart0 = Math<Real>::FAbs(kPerp.Dot(m_rkBox.Axis[0]));
    Real fPart1 = Math<Real>::FAbs(kPerp.Dot(m_rkBox.Axis[1]));
    fRhs = m_rkBox.Extent[0]*fPart0 + m_rkBox.Extent[1]*fPart1;
    return fLhs <= fRhs;
}