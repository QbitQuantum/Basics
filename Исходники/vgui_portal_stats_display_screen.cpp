void MakeTimeString( CFmtStr &str, int iHours, int iMinutes, int iSeconds )
{
	if ( iHours )
	{
		if ( iMinutes < 10 )
		{
			if ( iSeconds < 10 )
				str.sprintf( "%d:0%d:0%d", iHours, iMinutes, iSeconds );
			else
				str.sprintf( "%d:0%d:%d", iHours, iMinutes, iSeconds );
		}
		else
		{
			if ( iSeconds < 10 )
				str.sprintf( "%d:%d:0%d", iHours, iMinutes, iSeconds );
			else
				str.sprintf( "%d:%d:%d", iHours, iMinutes, iSeconds );
		}
	}
	else
	{
		if ( iSeconds < 10 )
			str.sprintf( "%d:0%d", iMinutes, iSeconds );
		else
			str.sprintf( "%d:%d", iMinutes, iSeconds );
	}
}