void FName::DisplayHash( FOutputDevice& Ar )
{
    int32 UsedBins=0, NameCount=0, MemUsed = 0;
    for( int32 i=0; i<ARRAY_COUNT(NameHash); i++ )
    {
        if( NameHash[i] != NULL ) UsedBins++;
        for( FNameEntry *Hash = NameHash[i]; Hash; Hash=Hash->HashNext )
        {
            NameCount++;
            // Count how much memory this entry is using
            MemUsed += FNameEntry::GetSize( Hash->GetNameLength(), Hash->IsWide() );
        }
    }
    Ar.Logf( TEXT("Hash: %i names, %i/%i hash bins, Mem in bytes %i"), NameCount, UsedBins, ARRAY_COUNT(NameHash), MemUsed);
}