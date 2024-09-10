void CPresenceDataCache::RemoveMeFromArray( RPointerArray< Type >& aItemArray, Type* aChild )
{
    TInt itemCount( aItemArray.Count() );
    for ( TInt i( 0 ); i < itemCount; i++ )
    {
        if ( aChild == aItemArray[ i ] )
        {
            aItemArray.Remove( i );
            break;
        }
    }
}