bool TEXTE_MODULE::TextHitTest( const EDA_RECT& aRect, bool aContains, int aAccuracy ) const
{
    EDA_RECT rect = aRect;

    rect.Inflate( aAccuracy );

    if( aContains )
    {
        return rect.Contains( GetBoundingBox() );
    }
    else
    {
        return rect.Intersects( GetTextBox( -1 ), GetDrawRotation() );
    }
}