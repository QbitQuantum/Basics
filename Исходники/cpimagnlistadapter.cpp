// -----------------------------------------------------------------------------
// CPIMAgnListAdapter::FetchNativeEntryL
// Fetches an entry according to a PIM item id.
// Returns: A calendar entry.
//          The ownership of the item is transferred to the caller.
// -----------------------------------------------------------------------------
//
CCalEntry* CPIMAgnListAdapter::FetchNativeEntryL(TPIMItemID aItemId,
        CCalEntry::TType aEntryType)
{
    JELOG2(EPim);
    EnsureOpenSessionL();
    __ASSERT_ALWAYS(aItemId != KPIMNullItemID, User::Leave(KErrArgument));

    RPointerArray<CCalEntry> entryArray;
    CleanupResetAndDestroyPushL(entryArray);
    iCalEntryView->FetchL(aItemId, entryArray);

    // Only one entry should be returned. NOTE that if there is no items
    // in the fetched array it means that the item might have been removed
    // so, we MUST NOT panic here as we did previously...
    __ASSERT_ALWAYS(entryArray.Count() > 0 && entryArray[0]->EntryTypeL()
                    == aEntryType, User::Leave(KErrNotFound));

    CCalEntry* entry = entryArray[0];
    // Take the ownership of the first item. Child instances are simply ignored
    entryArray.Remove(0);
    CleanupStack::PopAndDestroy(&entryArray);
    return entry;
}