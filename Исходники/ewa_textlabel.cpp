void EWATextLabel::drawBackground()
{
    QRect fullRect = rect();
    QRect roundedRect( QPoint( fullRect.topLeft().x()+1, fullRect.topLeft().y() ), QPoint( fullRect.width()-1, fullRect.height() ) );
    
    
    QPainter painter( this );
    
    painter.fillRect( fullRect, Qt::transparent );
    
    painter.setPen( Qt::NoPen );
    painter.setBrush( m_color );
    
    painter.setRenderHints( EWAApplication::getRenderHints() );
    painter.setOpacity(0.5);
    painter.drawRoundedRect( roundedRect, 5, 5, Qt::AbsoluteSize );
}