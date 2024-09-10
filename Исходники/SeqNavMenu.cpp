bool SeqNavMenu::StartBuildingForPredicate()
{
	BVolumeRoster 	roster;
	BVolume			volume;
	roster.Rewind();
	if( roster.GetBootVolume( &volume ) != B_OK ) {
		printf("couldn't get a volume\n");
		return false;
	}
	mQuery.Clear();
	mQuery.SetVolume( &volume );
	mQuery.SetPredicate( mPredicate.String() );
	if( mQuery.Fetch() != B_OK ) {
		printf("query can't fetch\n");
		return false;
	}
	return true;
}