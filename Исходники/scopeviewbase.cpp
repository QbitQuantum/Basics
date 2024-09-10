void ScopeViewBase::paintEvent( QPaintEvent * event )
{
	QRect r = event->rect();
	
	if (b_needRedraw)
	{
		//CALLGRIND_TOGGLE_COLLECT();
		
		updateOutputHeight();
		
		QPainter p;
		m_pixmap->fill( paletteBackgroundColor() );
		p.begin(m_pixmap);
		p.setClipRegion(event->region());
		
		//let the subclass draw the background (grids, etc.)
		drawBackground(p);
		
//		drawProbeMap(p, Oscilloscope::self()->m_logicProbeDataMap);	
//		drawProbeMap(p, Oscilloscope::self()->m_floatingProbeDataMap);	
		
		p.setPen(Qt::black);
		p.drawRect( frameRect() );
		
		b_needRedraw = false;
		
		//CALLGRIND_TOGGLE_COLLECT();
	}
	
	bitBlt( this, r.x(), r.y(), m_pixmap, r.x(), r.y(), r.width(), r.height() );
}