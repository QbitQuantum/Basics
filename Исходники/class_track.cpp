bool VIA::HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy ) const
{
    EDA_RECT box;
    EDA_RECT arect = aRect;
    arect.Inflate( aAccuracy );

    box.SetOrigin( GetStart() );
    box.Inflate( GetWidth() / 2 );

    if( aContained )
        return arect.Contains( box );
    else
        return arect.Intersects( box );
}