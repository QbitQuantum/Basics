/**
 * Prints the subtitle associated with the SoundWave to the console
 */
void USoundWave::LogSubtitle( FOutputDevice& Ar )
{
	FString Subtitle = "";
	for( int32 i = 0; i < Subtitles.Num(); i++ )
	{
		Subtitle += Subtitles[ i ].Text.ToString();
	}

	if( Subtitle.Len() == 0 )
	{
		Subtitle = SpokenText;
	}

	if( Subtitle.Len() == 0 )
	{
		Subtitle = "<NO SUBTITLE>";
	}

	Ar.Logf( TEXT( "Subtitle:  %s" ), *Subtitle );
#if WITH_EDITORONLY_DATA
	Ar.Logf( TEXT( "Comment:   %s" ), *Comment );
#endif // WITH_EDITORONLY_DATA
	Ar.Logf( bMature ? TEXT( "Mature:    Yes" ) : TEXT( "Mature:    No" ) );
}