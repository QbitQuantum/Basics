    bool IntrTriangle3Cylinder3<Real>::DiskOverlapsSegment (
        const Vector2<Real>& Q0, const Vector2<Real>& Q1 ) const
    {
        Real rSqr = mCylinder->Radius * mCylinder->Radius;
        Vector2<Real> D = Q0 - Q1;
        Real dot = Q0.Dot( D );
        if ( dot <= ( Real )0 )
        {
            return Q0.Dot( Q0 ) <= rSqr;
        }

        Real lenSqr = D.Dot( D );
        if ( dot >= lenSqr )
        {
            return Q1.Dot( Q1 ) <= rSqr;
        }

        dot = D.DotPerp( Q0 );
        return dot * dot <= lenSqr * rSqr;
    }