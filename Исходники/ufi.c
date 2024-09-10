VOID vFreeUFIHashTable(
 PUFIHASH *ppHashTable
)
{
    PUFIHASH pBucket, *ppHashEnd, pBucketTmp, *ppTableBase;

    if( ppHashTable == NULL )
    {
        return;
    }

    ppTableBase = ppHashTable;  // save ptr to the base so we can free it later

// Next loop through the whole table looking for buckets lists

    for( ppHashEnd = ppHashTable + UFI_HASH_SIZE;
         ppHashTable < ppHashEnd;
         ppHashTable += 1 )
    {
        pBucket = *ppHashTable;

        while( pBucket != NULL )
        {
            pBucketTmp = pBucket;
            pBucket = pBucket->pNext;
            LOCALFREE( pBucketTmp );
        }

    }

    LOCALFREE( ppTableBase );

}