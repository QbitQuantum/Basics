bool ZONE_CONTAINER::HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy ) const
{
    EDA_RECT arect = aRect;
    arect.Inflate( aAccuracy );
    EDA_RECT bbox = m_Poly->GetBoundingBox();
    bbox.Normalize();

    if( aContained )
         return arect.Contains( bbox );
    else    // Test for intersection between aRect and the polygon
            // For a polygon, using its bounding box has no sense here
    {
        // Fast test: if aRect is outside the polygon bounding box,
        // rectangles cannot intersect
        if( ! bbox.Intersects( arect ) )
            return false;

        // aRect is inside the polygon bounding box,
        // and can intersect the polygon: use a fine test.
        // aRect intersects the polygon if at least one aRect corner
        // is inside the polygon
        wxPoint corner = arect.GetOrigin();

        if( HitTestInsideZone( corner ) )
            return true;

        corner.x = arect.GetEnd().x;

        if( HitTestInsideZone( corner ) )
            return true;

        corner = arect.GetEnd();

        if( HitTestInsideZone( corner ) )
            return true;

        corner.x = arect.GetOrigin().x;

        if( HitTestInsideZone( corner ) )
            return true;

        // No corner inside arect, but outlines can intersect arect
        // if one of outline corners is inside arect
        int count = m_Poly->GetCornersCount();
        for( int ii =0; ii < count; ii++ )
        {
            if( arect.Contains( m_Poly->GetPos( ii ) ) )
                return true;
        }

        return false;
    }
}