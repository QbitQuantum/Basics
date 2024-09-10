// ---------------------------------------------------------------------------------
// CUpnpTmFilteredAppList::RemoveWhiteSpace
// Method is used to remove leading and trailing whitespaces from the descriptor's data
// @param aData Descriptor's data from which whitespaces have to be removed
// @return Returns the descriptor having no white spaces
// ---------------------------------------------------------------------------------
//
const TDesC8& CUpnpTmFilteredAppList::RemoveWhiteSpace( TPtrC8& aData )
    {
    OstTraceFunctionEntry0( CUPNPTMFILTEREDAPPLIST_REMOVEWHITESPACE_ENTRY );
    // Removes the leading white spaces
    TInt length = aData.Length();
    TInt i = 0;
    TBool done = EFalse;
    while( !done && i < length )
        {
        TChar current = aData[i];
        done  = !current.IsSpace();
        if( !done )
        ++i;
        }
    aData.Set(aData.Mid(i)); /* aData now does not have any white space character 
                                ahead of its actual data */
    
    // Removes the trailing white spaces
    length = aData.Length();
    i = 0;
    done = EFalse;
    while( !done && i < length )
        {
        TChar current = aData[(length-1) - i];
        done  = !current.IsSpace();
        if( !done )
        ++i;
        }
    aData.Set(aData.Left(aData.Length() - i)); /* aData now does not have any white space character
                                                following the actual data */
    OstTraceFunctionExit0( CUPNPTMFILTEREDAPPLIST_REMOVEWHITESPACE_EXIT );
    return aData;
    }