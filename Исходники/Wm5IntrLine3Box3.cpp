    bool IntrLine3Box3<Real>::DoClipping ( Real t0, Real t1,
                                           const Vector3<Real>& origin, const Vector3<Real>& direction,
                                           const Box3<Real>& box, bool solid, int& quantity, Vector3<Real> point[2],
                                           int& intrType )
    {
        // Convert linear component to box coordinates.
        Vector3<Real> diff = origin - box.Center;
        Vector3<Real> BOrigin(
            diff.Dot( box.Axis[0] ),
            diff.Dot( box.Axis[1] ),
            diff.Dot( box.Axis[2] )
        );
        Vector3<Real> BDirection(
            direction.Dot( box.Axis[0] ),
            direction.Dot( box.Axis[1] ),
            direction.Dot( box.Axis[2] )
        );

        Real saveT0 = t0, saveT1 = t1;
        bool notAllClipped =
            Clip( +BDirection.X(), -BOrigin.X() - box.Extent[0], t0, t1 ) &&
            Clip( -BDirection.X(), +BOrigin.X() - box.Extent[0], t0, t1 ) &&
            Clip( +BDirection.Y(), -BOrigin.Y() - box.Extent[1], t0, t1 ) &&
            Clip( -BDirection.Y(), +BOrigin.Y() - box.Extent[1], t0, t1 ) &&
            Clip( +BDirection.Z(), -BOrigin.Z() - box.Extent[2], t0, t1 ) &&
            Clip( -BDirection.Z(), +BOrigin.Z() - box.Extent[2], t0, t1 );

        if ( notAllClipped && ( solid || t0 != saveT0 || t1 != saveT1 ) )
        {
            if ( t1 > t0 )
            {
                intrType = IT_SEGMENT;
                quantity = 2;
                point[0] = origin + t0 * direction;
                point[1] = origin + t1 * direction;
            }
            else
            {
                intrType = IT_POINT;
                quantity = 1;
                point[0] = origin + t0 * direction;
            }
        }
        else
        {
            quantity = 0;
            intrType = IT_EMPTY;
        }

        return intrType != IT_EMPTY;
    }