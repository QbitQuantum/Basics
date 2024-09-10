/*virtual*/ void UIWidgetText::Tick( const float DeltaTime )
{
	XTRACE_FUNCTION;

	if( !m_Velocity.IsZero() )
	{
		m_TopLeft += m_Velocity * DeltaTime;

		if( m_ClampToPixelGrid )
		{
			// Floor instead of round so we don't mess with the velocity.
			// (Essentially the same as subtracting the half pixel offset
			// before rounding, since it just adds 0.5.)
			const float PixelGridOffset = 0.5f - GetPixelGridOffset();
			m_TopLeft.x = Floor( m_TopLeft.x ) + PixelGridOffset;
			m_TopLeft.y = Floor( m_TopLeft.y ) + PixelGridOffset;
		}

		UpdateRenderPosition();
	}
}