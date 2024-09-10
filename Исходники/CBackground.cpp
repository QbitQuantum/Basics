//**********************************************************************************
//	
//**********************************************************************************
void	CBackground::Open()
{
	CRenderable::Register( CRenderable::RO_BACKGROUND, Render );

	for ( u32 i = 0; i < NUM_STRIPS; ++i )
	{
		s_StripInfo[ i ].m_SinPos += ( rand() % 2000 ) / 1000.f;
	}

	time_t		localTime( time( NULL ) );
	struct tm *	p_calendar_time( gmtime( &localTime ) );

	SetBackgroundImage( p_calendar_time->tm_mon + 1 );
}