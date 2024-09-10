void CMeteorite::Draw( QPainter &painter, const float freq_tick )
{
	painter.setPen( QPen( meteo_clr, 1 ) );


	float tx = 0, ty = 0;
	getTickCoords( freq_tick, tx, ty );

	QPolygon m_tmp_bd( m_body );
	m_tmp_bd.translate( tx, ty );

	painter.drawPolygon( m_tmp_bd );

	QPainterPath pt;
	pt.addPolygon( m_tmp_bd );


	painter.fillPath( pt, QBrush( Qt::black ));
	painter.fillPath( pt, QBrush( meteo_clr, Qt::Dense2Pattern ));

}