//! Set the color map to be used.
void medImageMaskAnnotationData::setColorMap( const ColorMapType & colorMap )
{
    m_colorMap = colorMap;
    qSort( m_colorMap );
}