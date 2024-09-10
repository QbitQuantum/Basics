void
FormResizableProxy::handleMoved( const QPointF & delta, FormMoveHandle * handle )
{
	if( !d->m_handleMoved )
	{
		d->m_subsidiaryRect = d->m_rect;

		d->m_handleMoved = true;
	}

	if( handle == d->m_handles->m_move.data() )
	{
		d->m_rect.moveTop( d->m_rect.top() + delta.y() );
		d->m_rect.moveRight( d->m_rect.right() + delta.x() );

		setRect( d->m_rect );

		d->m_object->moveResizable( delta );
	}
	else if( handle == d->m_handles->m_topLeft.data() )
	{
		const QRectF r = d->m_rect.adjusted( delta.x(), delta.y(), 0.0, 0.0 );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_top.data() )
	{
		const QRectF r = d->m_rect.adjusted( 0.0, delta.y(), 0.0, 0.0 );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_topRight.data() )
	{
		const QRectF r = d->m_rect.adjusted( 0.0, delta.y(), delta.x(), 0.0 );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_right.data() )
	{
		const QRectF r = d->m_rect.adjusted( 0.0, 0.0, delta.x(), 0.0 );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_bottomRight.data() )
	{
		const QRectF r = d->m_rect.adjusted( 0.0, 0.0, delta.x(), delta.y() );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_bottom.data() )
	{
		const QRectF r = d->m_rect.adjusted( 0.0, 0.0, 0.0, delta.y() );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_bottomLeft.data() )
	{
		const QRectF r = d->m_rect.adjusted( delta.x(), 0.0, 0.0, delta.y() );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
	else if( handle == d->m_handles->m_left.data() )
	{
		const QRectF r = d->m_rect.adjusted( delta.x(), 0.0, 0.0, 0.0 );

		if( d->m_handles->checkConstraint( r.size() ) )
			setRect( r );
	}
}