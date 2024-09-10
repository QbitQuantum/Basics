void SkyQPainter::drawSkyBackground()
{
    //FIXME use projector
    fillRect( 0, 0, m_size.width(), m_size.height(), KStarsData::Instance()->colorScheme()->colorNamed( "SkyColor" ) );
}