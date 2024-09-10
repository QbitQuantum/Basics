    bool IntrLine2Box2<Real>::DoClipping ( Real t0, Real t1,
                                           const Vector2<Real>& origin, const Vector2<Real>& direction,
                                           const Box2<Real>& box, bool solid, int& quantity, Vector2<Real> point[2],
                                           int& intrType )
    {
        // Convert linear component to box coordinates.
        Vector2<Real> diff = origin - box.Center;
        Vector2<Real> BOrigin(
            diff.Dot( box.Axis[0] ),
            diff.Dot( box.Axis[1] )
        );
        Vector2<Real> BDirection(
            direction.Dot( box.Axis[0] ),
            direction.Dot( box.Axis[1] )
        );

        Real saveT0 = t0, saveT1 = t1;
        bool notAllClipped =
            Clip( +BDirection.X(), -BOrigin.X() - box.Extent[0], t0, t1 ) &&
            Clip( -BDirection.X(), +BOrigin.X() - box.Extent[0], t0, t1 ) &&
            Clip( +BDirection.Y(), -BOrigin.Y() - box.Extent[1], t0, t1 ) &&
            Clip( -BDirection.Y(), +BOrigin.Y() - box.Extent[1], t0, t1 );

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
            intrType = IT_EMPTY;
            quantity = 0;
        }

        return intrType != IT_EMPTY;
    }