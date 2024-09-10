// OutputProgress
//------------------------------------------------------------------------------
/*static*/ void FLog::OutputProgress( float time, 
									  float percentage,
									  uint32_t numJobs, 
									  uint32_t numJobsActive, 
									  uint32_t numJobsDist, 
									  uint32_t numJobsDistActive )
{
    PROFILE_FUNCTION

	ASSERT( s_ShowProgress );

	// format progress % (we know it never goes above 99.9%)
	uint32_t intPerc = (uint32_t)( percentage * 10.0f ); // 0 to 999
	uint32_t hundreds = ( intPerc / 100 ); intPerc -= ( hundreds * 100 );
	uint32_t tens = ( intPerc / 10 ); intPerc -= ( tens * 10 );
	uint32_t ones = intPerc;
	m_ProgressText = g_OutputString;
	m_ProgressText[ 1 ] = ( hundreds > 0 ) ? ( '0' + (char)hundreds ) : ' ';
	m_ProgressText[ 2 ] = '0' + (char)tens;
	m_ProgressText[ 4 ] = '0' + (char)ones;

	// 20 column output (100/20 = 5% per char)
	uint32_t numStarsDone = (uint32_t)( percentage * 20.0f / 100.0f ); // 20 columns
	for ( uint32_t i=0; i<20; ++i ) 
	{
		m_ProgressText[ 9 + i ] = ( i < numStarsDone ) ? '*' : '-';
	}

	// time " [%um] %02us"
	uint32_t timeTakenMinutes = uint32_t( time / 60.0f );
	uint32_t timeTakenSeconds = (uint32_t)time - ( timeTakenMinutes * 60 );
	if ( timeTakenMinutes > 0 )
	{
		char buffer[ 8 ];
		_itoa_s( timeTakenMinutes, buffer, 8, 10 );
		m_ProgressText += buffer;
		m_ProgressText.Append( "m ", 2 );
	}
	char buffer[ 8 ];
	_itoa_s( timeTakenSeconds, buffer, 8, 10 );
	if ( timeTakenSeconds < 10 ) { m_ProgressText += '0'; }
	m_ProgressText += buffer;
	m_ProgressText += 's';

	// active/available jobs " (%u/%u)"
	m_ProgressText.Append( " (", 2 );
	_itoa_s( numJobsActive, buffer, 8, 10 );
	m_ProgressText += buffer;
	m_ProgressText += '/';
	_itoa_s( numJobsActive + numJobs, buffer, 8, 10 );
	m_ProgressText += buffer;
	m_ProgressText += ')';

	// distributed status "+(%u/%u)"
	if ( FBuild::Get().GetOptions().m_AllowDistributed )
	{
		m_ProgressText.Append( "+(", 2 );
		_itoa_s( numJobsDistActive, buffer, 8, 10 );
		m_ProgressText += buffer;
		m_ProgressText += '/';
		_itoa_s( numJobsDistActive + numJobsDist, buffer, 8, 10 );
		m_ProgressText += buffer;
		m_ProgressText += ')';
	}

	m_ProgressText.Append( "    \b\b\b", 7 ); // extra whitespace when string shortens

	// if build aborting, override all output
	if ( FBuild::Get().GetStopBuild() )
	{
		m_ProgressText.Format( "\rBUILD ABORTED - STOPPING (%u) ", numJobsActive );
		m_ProgressText += "                                  \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	}

	// animation
	static int animIndex = 0;
	static char anim[] = { '\\', '|', '/', '-', '\\', '|', '/', '-' };
	m_ProgressText += anim[ ( animIndex++ ) % 8 ]; 

	// finally print it
	fwrite( m_ProgressText.Get(), 1, m_ProgressText.GetLength(), stdout );
}