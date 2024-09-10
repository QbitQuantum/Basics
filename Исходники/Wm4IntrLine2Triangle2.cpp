void IntrLine2Triangle2<Real>::GetInterval (const Vector2<Real>& rkOrigin,
    const Vector2<Real>& rkDirection, const Triangle2<Real>& rkTriangle,
    const Real afDist[3], const int aiSign[3], Real afParam[2])
{
    // Project triangle onto line.
    Real afProj[3];
    int i;
    for (i = 0; i < 3; i++)
    {
        Vector2<Real> kDiff = rkTriangle.V[i] - rkOrigin;
        afProj[i] = rkDirection.Dot(kDiff);
    }

    // Compute transverse intersections of triangle edges with line.
    Real fNumer, fDenom;
    int i0, i1, i2;
    int iQuantity = 0;
    for (i0 = 2, i1 = 0; i1 < 3; i0 = i1++)
    {
        if (aiSign[i0]*aiSign[i1] < 0)
        {
            assert(iQuantity < 2);
            fNumer = afDist[i0]*afProj[i1] - afDist[i1]*afProj[i0];
            fDenom = afDist[i0] - afDist[i1];
            afParam[iQuantity++] = fNumer/fDenom;
        }
    }

    // Check for grazing contact.
    if (iQuantity < 2)
    {
        for (i0 = 1, i1 = 2, i2 = 0; i2 < 3; i0 = i1, i1 = i2++)
        {
            if (aiSign[i2] == 0)
            {
                assert(iQuantity < 2);
                afParam[iQuantity++] = afProj[i2];
            }
        }
    }

    // Sort.
    assert(iQuantity >= 1);
    if (iQuantity == 2)
    {
        if (afParam[0] > afParam[1])
        {
            Real fSave = afParam[0];
            afParam[0] = afParam[1];
            afParam[1] = fSave;
        }
    }
    else
    {
        afParam[1] = afParam[0];
    }
}