// -----------------------------------------------------------------------------
// TMccResourceContainerIterator::Delete
// -----------------------------------------------------------------------------
//
TInt TMccResourceContainerIterator::Delete( RPointerArray<CMccResourceContainer>& aContainers )
    {
    TInt currentIndex = Current();
    
    if ( currentIndex != KErrNotFound && currentIndex < aContainers.Count() )
        {
        delete aContainers[ currentIndex ];
        aContainers.Remove( currentIndex );
        iCurrentIndex = currentIndex;
        }
    
    return currentIndex;
    }