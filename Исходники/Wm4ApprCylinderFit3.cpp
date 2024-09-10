CylinderFit3<Real>::CylinderFit3 (int iQuantity, const Vector3<Real>* akPoint,
    Vector3<Real>& rkC, Vector3<Real>& rkU, Real& rfR, Real& rfH,
    bool bInputsAreInitialGuess)
{
    Real fInvRSqr = (Real)1.0;
    if (!bInputsAreInitialGuess)
    {
        // Find the least-squares line that fits the data and use it as an
        // initial guess for the cylinder axis.
        Line3<Real> kLine = OrthogonalLineFit3(iQuantity,akPoint);
        rkC = kLine.Origin;
        rkU = kLine.Direction;
    }

    m_fError = Math<Real>::MAX_REAL;
    const int iMax = 8;
    int i;
    for (i = 0; i < iMax; i++)
    {
        m_fError = UpdateInvRSqr(iQuantity,akPoint,rkC,rkU,fInvRSqr);
        m_fError = UpdateDirection(iQuantity,akPoint,rkC,rkU,fInvRSqr);
        m_fError = UpdateCenter(iQuantity,akPoint,rkC,rkU,fInvRSqr);
    }

    // Compute the radius.
    rfR = Math<Real>::InvSqrt(fInvRSqr);

    // Project points onto fitted axis to determine extent of cylinder along
    // the axis.
    Real fTMin = rkU.Dot(akPoint[0]-rkC), fTMax = fTMin;
    for (i = 1; i < iQuantity; i++)
    {
        Real fT = rkU.Dot(akPoint[i]-rkC);
        if (fT < fTMin)
        {
            fTMin = fT;
        }
        else if (fT > fTMax)
        {
            fTMax = fT;
        }
    }

    // Compute the height.  Adjust the center to point that projects to
    // midpoint of extent.
    rfH = fTMax - fTMin;
    rkC += ((Real)0.5)*(fTMin+fTMax)*rkU;
}