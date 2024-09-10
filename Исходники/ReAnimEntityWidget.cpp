void ReAnimEntityWidget::OnScaleChanged( const QPointF& _scale )
{
	ReAnimTrackWidget* trackWidget = m_suiteArray[ ETrackType_Scale ].m_track;
	if( NULL != trackWidget )
	{
		bool isDirty = false;
		ReAnimFrameWidget* frameWidget = trackWidget->GetFrameAtCursor( trackWidget->GetCursor() );
		if( NULL == frameWidget )
		{
			frameWidget = trackWidget->CreateFrameAtCursor( trackWidget->GetCursor() );
			isDirty = true;
		}

		ReAnimFrame* frameData = frameWidget->GetModelData();
		frameData->SetFrameValue( _scale.x(), 0 );
		frameData->SetFrameValue( _scale.y(), 1 );

		if( isDirty )
			update();
	}
}