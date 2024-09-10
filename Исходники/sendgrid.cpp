// Set grid items from a resource
void CSendGrid::SetItemsL(TInt aResourceId) {

    // Clear previous items if we already have an item array, otherwise create
    // it
    if ( iItemArray ) {
        iGrid->SetCurrentItemIndex(0);
        iItemArray->Reset();
        iGrid->HandleItemRemovalL();
    } else {
        iItemArray = new (ELeave) CDesCArrayFlat(12);
        iGrid->Model()->SetItemTextArray(iItemArray);
    }
    
    // Read items from the resource file
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader, aResourceId);
    TInt count = reader.ReadInt16();
    __ASSERT_ALWAYS(count == KSendGridNumItems,
                    User::Panic(KPanic, KPanicBadResource));
    for ( TInt i = 0; i < count; i++ ) {
        iCommands[i] = reader.ReadInt32();
        iSubGrids[i] = reader.ReadInt32();
        TBuf<32> buf;
        buf.Append('\t');
        buf.Append(KGridItemLabels[i]);
        buf.Append('\t');
        TPtrC ptr = reader.ReadTPtrC();
        __ASSERT_ALWAYS(ptr.Length() <= 30,
                    User::Panic(KPanic, KPanicBadResource));
        buf.Append(ptr);
        iItemArray->AppendL(buf);
    }    
    CleanupStack::PopAndDestroy(); // reader
    iGrid->HandleItemAdditionL();
    iGrid->SetCurrentItemIndex(0);
    iCurrentGrid = aResourceId;
}