bool SCH_SHEET::IsSelectStateChanged( const wxRect& aRect )
{
    bool previousState = IsSelected();

    EDA_RECT boundingBox = GetBoundingBox();

    if( aRect.Intersects( boundingBox ) )
        SetFlags( SELECTED );
    else
        ClearFlags( SELECTED );

    return previousState != IsSelected();
}