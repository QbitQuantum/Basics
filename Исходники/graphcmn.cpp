void wxGraphicsContext::DrawPath( const wxGraphicsPath& path, int fillStyle )
{
    FillPath( path , fillStyle );
    StrokePath( path );
}