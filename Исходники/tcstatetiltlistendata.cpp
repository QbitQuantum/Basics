// -----------------------------------------------------------------------------
// CTCStateTiltListenData::PrepareArray
// -----------------------------------------------------------------------------
//
// Prepares array for item insertion
static void PrepareArray( RArray<TTiltXYZValue>& aArray, TInt aItemsToInsert, TInt aMaxItems )
    {
    FUNC_LOG;
    
    TInt count = aArray.Count();
    TInt i = count + aItemsToInsert;
    while( i-- > aMaxItems ) // Delete old items from end
        {
        aArray.Remove( --count );
        }
    }