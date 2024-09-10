void UTexAligner::Align( UWorld* InWorld, ETexAlign InTexAlignType )
{
	for( int32 LevelIndex = 0; LevelIndex < InWorld->GetNumLevels(); ++LevelIndex )
	{
		ULevel* Level = InWorld->GetLevel(LevelIndex);
		Align( InWorld, InTexAlignType, Level->Model );
	}
}