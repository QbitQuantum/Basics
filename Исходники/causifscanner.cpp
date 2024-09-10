// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//
void CCaUsifScanner::FindDeletedEntriesL(
        RPointerArray<CCaInnerEntry>& aCaArray, const RPointerArray<
                CComponentEntry>& aUsifArray )
    {
    for( TInt i( aCaArray.Count() - 1 ); i >= 0; i-- )
        {
        TBuf<KMaxUnits> compIdDes;
        if( aCaArray[i]->FindAttribute( KCaAttrComponentId, compIdDes ) )
            {
            TLex lex( compIdDes );
            TUint uint( 0 );
            User::LeaveIfError( lex.Val( uint ) );
            //for each usif entry check if entry has to be removed
            for( TInt k( 0 ); k < aUsifArray.Count(); k++ )
                {
                if( aUsifArray[k]->ComponentId() == uint)
                    {
                    delete aCaArray[i];
                    aCaArray.Remove( i );
                    break;
                    }
                }
            }
        }
    }